#include "stdafx.h"
#include "Neuron.h"
#include "NeuralNetwork.h"
#include "time.h"
#include "WAV.h"



int main(int argc, char *argv[])
{
	//Initialisation 
	std::cout << "INIT" << std::endl;
	srand((int)time(NULL));


	//Reseau
	NeuralNetwork _network (BUFFER_SIZE);
   


	WAV _inputWav, _sampleWav;
	
    if (_inputWav.Read("data/sum41.wav") || _sampleWav.Read("data/sum41.wav"))
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


    short _sampleBuffer[BUFFER_SIZE];
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        _sampleBuffer[i] = ((short*)_sampleWav.getData())[i];
    }

    _network.findWeight(_sampleBuffer);


    int _endBytePos = min(30000, (int)_inputWav.getSampleCount());

    short* _inputData = (short*) _inputWav.getData();
	short* _outputData = new short[_endBytePos];
    memcpy(_outputData, _inputData, _endBytePos * sizeof(short));


	for (int i = 0; i < 1000; i ++)
	{
        if (i % 100 == 0)
            cout << i << endl;

        // ajoute d'une onde aléatoire à l'échantillon
        int range = 1024;
        float freq = (float) random(20, 1000);
        int p = random(0, _endBytePos - range);
        
        for (int j = p; j < p + range; j++)
        {
            float a = (float)(j - p) / (float)_inputWav.getSampleRate();
            _outputData[j] = (short) ((float) _outputData[j] + 1000.f * sin(a * 2.f * 3.141596f * freq));
        }

        // test avec le reseau de neurone, l'echantillon avant et après
        REAL _score0 = _network.test(_inputData, p, p + range);
        REAL _score1 = _network.test(_outputData, p, p + range);

        // si le reseau de neurone est content
        if (_score1 > _score0)
        {
            // on garde le buffer modifié
            memcpy(_inputData, _outputData, _endBytePos * sizeof(short));
            //cout << "OK" << endl;
        }
        else
        {
            // on ecrase le buffer modifié
            memcpy(_outputData, _inputData, _endBytePos * sizeof(short));
            //cout << "NOK" << endl;
        }
	}

    // écrit le son final
    _inputWav.setSampleCount(_endBytePos);
    _inputWav.setData(_outputData, _endBytePos * sizeof(short));
    cout << "write out.wav" << endl;
    _inputWav.Write("out.wav");

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
REAL NeuralNetwork::getInput(int fInput, short* fBuffer)
{
	if (fInput < BUFFER_SIZE)
		return (REAL)fBuffer[fInput];
	else
		return 0.L;
}


// Calcul les poids des neurones 
void NeuralNetwork::findWeight(short* fBuffer)
{
	
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        mNeuronArray[i]->setWeight(fBuffer[i]);
    }
	
}

REAL NeuralNetwork::test(short* fData, int fStart, int fEnd)
{
    REAL _score = 0;

    for (int i = fStart; i < fEnd; i++)
    {
        _score += mNeuronArray.back()->getOutput(&fData[i]);
    }

    return _score;
}
