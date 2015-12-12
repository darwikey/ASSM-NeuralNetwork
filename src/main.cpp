#include "stdafx.h"
#include "NeuralNetwork.h"
#include "time.h"
#include "WAV.h"
#include "kiss_fft.h"
#include "Generator.h"


void normalizeFFT(std::vector<kiss_fft_cpx>& fBuffer)
{
    float _max = 0.f;
    for (unsigned int i = 0; i < BUFFER_SIZE / 2; i++)
    {
        fBuffer[i].r = fabs(fBuffer[i].r);
        if (fBuffer[i].r > _max)
        {
            _max = fBuffer[i].r;
        }
    }
    if (_max > 1e-6f)
    {
        for (unsigned int i = 0; i < BUFFER_SIZE / 2; i++)
        {
            fBuffer[i].r /= _max;
        }
    }
}


int main(int argc, char *argv[])
{
    //************************************************************
    // Initialisation
    //************************************************************
	std::cout << "INIT" << std::endl;
	srand((int)time(NULL));

    // Charge les fichiers audio
	WAV _inputWav, _sampleWav;
	
    if (_inputWav.Read("data/ellie.wav") || _sampleWav.Read("data/ellie.wav"))
	{
        std::cerr << "unable to read file" << std::endl;
		return EXIT_FAILURE;
	}

    if (_inputWav.getChannels() != 1 || _sampleWav.getChannels() != 1)
    {
        std::cerr << "stereo sounds are not supported" << std::endl;
        return EXIT_FAILURE;
    }

    if (_inputWav.getBit() != 16 || _sampleWav.getBit() != 16)
    {
        std::cerr << "sounds must be 16 bits" << std::endl;
        return EXIT_FAILURE;
    }



    // init buffers
    std::vector<kiss_fft_cpx> _fftIn(BUFFER_SIZE);
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        _fftIn[i].r = ((short*) _sampleWav.getData())[i] / 32767.f;
        _fftIn[i].i = 0.f;
    }

    // lance FFT
    kiss_fft_cfg _fftCfg = kiss_fft_alloc(BUFFER_SIZE, 0, 0, 0);
    std::vector<kiss_fft_cpx> _fftOut(BUFFER_SIZE);
    kiss_fft(_fftCfg, _fftIn.data(), _fftOut.data());
    normalizeFFT(_fftOut);

    // Reseaux de neruones
    std::vector<NeuralNetwork*> _pool (200);
    for (unsigned int i = 0; i < _pool.size(); i++)
    {
        NeuralNetwork* _network = new NeuralNetwork();
        _pool[i] = _network;
    }


    Generator _generator;
    std::vector<float> _generatorParam(GENERATOR_SIZE, 0.f);
    std::vector<kiss_fft_cpx> _outGenerator(BUFFER_SIZE);
    std::vector<kiss_fft_cpx> _fftGenerator(BUFFER_SIZE);


    //************************************************************
    // Algorithme g�n�tique pour trouver un bon r�seau de neurone 
    //************************************************************
    for (int _generation = 0; _generation < 50; _generation++)
	{
        std::cout << "generation : " << _generation << std::endl;

        for (unsigned int i = 0; i < _pool.size(); i++)
        {
            // test avec le reseau de neurone
            _pool[i]->run(_fftOut, _generatorParam);

            // genere le son
            _generator.run(_generatorParam, _outGenerator, (float) _sampleWav.getSampleRate());

            // FFT du signal g�n�r�
            kiss_fft(_fftCfg, _outGenerator.data(), _fftGenerator.data());
            normalizeFFT(_fftGenerator);

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

        // croisement genetique entre les meilleurs r�seaux de neurones
        int _selection = (int)_pool.size() / 3;
        for (int i = 0; i < _selection; i++)
        {
            NeuralNetwork* _nn = new NeuralNetwork(_pool[i], _pool[random(0, _selection)]);

            // detruit les reseaux les plus mauvais et les remplace par des enfants
            delete _pool[_pool.size() - 1 - i];
            _pool[_pool.size() - 1 - i] = _nn;
        }
	}


    //************************************************************
    // Ecriture du son final
    //************************************************************

    // test avec le meilleur reseau de neurone
    std::sort(_pool.begin(), _pool.end(), &NeuralNetwork::sortFct);
    _pool[0]->run(_fftOut, _generatorParam);

    // genere le son
    std::vector<short> _outputData(_inputWav.getSampleCount());
    _outGenerator.resize(_outputData.size());
    _generator.run(_generatorParam, _outGenerator, (float) _sampleWav.getSampleRate());
    
    // convertit en entier 16 bits
    for (unsigned int i = 0; i < _outputData.size(); i++)
    {
        _outputData[i] = (short)(32767.f * _outGenerator[i].r);
    }

    _inputWav.setSampleCount(_outputData.size());
    _inputWav.setData(_outputData.data(), _outputData.size() * sizeof(short));
    std::cout << "write out.wav" << std::endl;
    _inputWav.Write("out.wav");

	return 0;
}