#include "stdafx.h"
#include "Neuron.h"
#include "NeuralNetwork.h"
#include "time.h"
#include "WAV.h"
#include "kiss_fft.h"
#include "Generator.h"



int main(int argc, char *argv[])
{
	//Initialisation 
	std::cout << "INIT" << std::endl;
	srand((int)time(NULL));





	WAV _inputWav, _sampleWav;
	
    if (_inputWav.Read("data/triangle.wav") || _sampleWav.Read("data/triangle.wav"))
	{
		return EXIT_FAILURE;
	}

    if (_inputWav.getChannels() != 1 || _sampleWav.getChannels() != 1)
    {
        cerr << "stereo sounds are not supported" << endl;
        return EXIT_FAILURE;
    }

    if (_inputWav.getBit() != 16 || _sampleWav.getBit() != 16)
    {
        cerr << "sounds must be 16 bits" << endl;
        return EXIT_FAILURE;
    }



    // init buffers
    kiss_fft_cpx _fftIn[BUFFER_SIZE];
    short _sampleBuffer[BUFFER_SIZE];
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        _sampleBuffer[i] = ((short*) _sampleWav.getData())[i];
        _fftIn[i].r = (float) _sampleBuffer[i] / 32767.f;
        _fftIn[i].i = 0.f;
    }

    // lance FFT
    kiss_fft_cfg cfg = kiss_fft_alloc(BUFFER_SIZE, 0, 0, 0);
    std::vector<kiss_fft_cpx> _fftOut(BUFFER_SIZE);
    kiss_fft(cfg, _fftIn, _fftOut.data());


    //Reseau
    NeuralNetwork _network(BUFFER_SIZE);
    _network.findWeight();


    //int _endBytePos = min(30000, (int)_inputWav.getSampleCount());

    Generator _generator;
    std::vector<float> _generatorParam(GENERATOR_SIZE, 0.f);
    std::vector<float> _outGenerator(BUFFER_SIZE, 0.f);

	for (int i = 0; i < 1; i ++)
	{
        if (i % 100 == 0)
            cout << i << endl;

        // test avec le reseau de neurone
        _network.run(_fftOut, _generatorParam);

        // genere le son
        _generator.run(_generatorParam, _outGenerator, (float) _sampleWav.getSampleRate());

        // calcul la distance de hammington entre les deux sons
        float _distance = 0.f;
        for (unsigned int j = 0; j < BUFFER_SIZE; j++)
        {
            _distance += fabs(_outGenerator[j] - _fftIn[j].r);
        }


	}

    // écrit le son final
    /*_inputWav.setSampleCount(_endBytePos);
    _inputWav.setData(_outputData, _endBytePos * sizeof(short));
    cout << "write out.wav" << endl;
    _inputWav.Write("out.wav");*/

	return 0;
}


// Constructeur réseau de neurones
NeuralNetwork::NeuralNetwork(int fNumInput) : mNumInput(fNumInput)
{
	mNumOutput = 1;

	//entrée
	for (int i=0; i<mNumInput; i++)
	{
		Neuron* _neuron = new Neuron(this, -i-1);
		mNeuronArray.push_back(_neuron);
	}

	// sortie
	for (int i=mNumInput; i < mNumInput +mNumOutput; i++)
	{
		Neuron* _neuron = new Neuron(this, 0, mNumInput-1);
		mNeuronArray.push_back(_neuron);
	}
}


// Renvoie l'entrée
REAL NeuralNetwork::getInput(int fInput, const std::vector<kiss_fft_cpx>& fBuffer)
{
	if (fInput < (int)fBuffer.size())
		return (REAL)fBuffer[fInput].r;
	else
		return 0.L;
}


// Calcul les poids des neurones 
void NeuralNetwork::findWeight()
{
	
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        mNeuronArray[i]->setWeight(random(-0.01L, 0.01L));
    }
	
}

void NeuralNetwork::run(const std::vector<kiss_fft_cpx>& fData, vector<float>& fOut)
{
    for (int i = 0; i < (int)fOut.size(); i++)
    {
        fOut[i] = mNeuronArray.back()->getOutput(fData);
    }
}
