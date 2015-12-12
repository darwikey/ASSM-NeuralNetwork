#include "stdafx.h"
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
    kiss_fft_cfg _fftCfg = kiss_fft_alloc(BUFFER_SIZE, 0, 0, 0);
    std::vector<kiss_fft_cpx> _fftOut(BUFFER_SIZE);
    kiss_fft(_fftCfg, _fftIn, _fftOut.data());


    // Reseaux de neruones
    std::vector<NeuralNetwork*> _pool (100);
    for (unsigned int i = 0; i < _pool.size(); i++)
    {
        NeuralNetwork* _network = new NeuralNetwork();
        _pool[i] = _network;
    }


    Generator _generator;
    std::vector<float> _generatorParam(GENERATOR_SIZE, 0.f);
    std::vector<kiss_fft_cpx> _outGenerator(BUFFER_SIZE);
    std::vector<kiss_fft_cpx> _fftGenerator(BUFFER_SIZE);

    for (int _generation = 0; _generation < 1; _generation++)
	{
        cout << "generation : " << _generation << endl;

        for (unsigned int i = 0; i < _pool.size(); i++)
        {
            // test avec le reseau de neurone
            _pool[i]->run(_fftOut, _generatorParam);

            // genere le son
            _generator.run(_generatorParam, _outGenerator, (float) _sampleWav.getSampleRate());

            // FFT du signal généré
            kiss_fft(_fftCfg, _outGenerator.data(), _fftGenerator.data());

            // calcul la distance entre les deux FFTs
            float _distance = 0.f;
            for (unsigned int j = 0; j < BUFFER_SIZE/2; j++)
            {
                _distance += fabs(_fftGenerator[j].r - _fftOut[j].r);
            }

            // plus le score est petit, mieux c'est
            _pool[i]->mScore = _distance;
        }

        // Trie la pool dans l'ordre croissant de score
        std::sort(_pool.begin(), _pool.end(), &NeuralNetwork::sortFct);

        std::cout << "best network : " << _pool[0]->mScore << std::endl;

	}


    // écrit le son final

    // test avec le meilleur reseau de neurone
    _pool[0]->run(_fftOut, _generatorParam);

    // genere le son
    std::vector<short> _outputData(_inputWav.getSampleCount());
    _outGenerator.resize(_outputData.size());
    _generator.run(_generatorParam, _outGenerator, (float) _sampleWav.getSampleRate());
    
    // convertit en short
    for (unsigned int i = 0; i < _outputData.size(); i++)
    {
        _outputData[i] = (short)(32767.f * _outGenerator[i].r);
    }

    _inputWav.setSampleCount(_outputData.size());
    _inputWav.setData(_outputData.data(), _outputData.size() * sizeof(short));
    cout << "write out.wav" << endl;
    _inputWav.Write("out.wav");

	return 0;
}


// Constructeur réseau de neurones
NeuralNetwork::NeuralNetwork() : mNumInput(BUFFER_SIZE), mNumOutput(GENERATOR_SIZE)
{
    for (int i = 0; i < mNumOutput; i++)
    {
        std::vector<float> _weights(mNumInput);

        for (int j = 0; j < mNumInput; j++)
        {
            float _w = random(0.f, 1.f / mNumInput);
            if (random(0, 100) > 33)
            {
                _w /= 50.f;
            }
            _weights[j] = _w;
        }

        mNeuronArray.push_back(_weights);
    }
}



void NeuralNetwork::run(const std::vector<kiss_fft_cpx>& fInput, vector<float>& fOut)
{
    for (int i = 0; i < (int)fOut.size(); i++)
    {
        float _out = 0.f;

        for (int j = 0; j < mNumInput / 2; j++)
        {
            _out += mNeuronArray[i][j] * fInput[j].r;
        }

        fOut[i] = _out;
    }
}


bool NeuralNetwork::sortFct(const NeuralNetwork* a, const NeuralNetwork* b)
{
    return a->mScore < b->mScore;
}
