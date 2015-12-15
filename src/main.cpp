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

    if (argc < 3)
    {
        std::cerr << "not enough parameters" << std::endl << "usage : ./NeuralNetwork sample_sound.wav sound_to_process.wav  [output_sound.wav]" << std::endl;
        return EXIT_FAILURE;
    }

    // Charge les fichiers audio
	WAV _inputWav, _sampleWav;
	
    if (_inputWav.Read(argv[2]) || _sampleWav.Read(argv[1]))
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

    if (_inputWav.getSampleCount() < BUFFER_SIZE || _sampleWav.getSampleCount() < BUFFER_SIZE)
    {
        std::cerr << "sounds are too smalls" << std::endl;
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
    std::vector<NeuralNetwork*> _pool (POOL_SIZE);
    for (unsigned int i = 0; i < _pool.size(); i++)
    {
        NeuralNetwork* _network = new NeuralNetwork();
        _pool[i] = _network;
    }


    Generator _generator;
    std::vector<float> _generatorParam(GENERATOR_COUNT, 0.f);
    std::vector<kiss_fft_cpx> _outGenerator(BUFFER_SIZE);
    std::vector<kiss_fft_cpx> _fftGenerator(BUFFER_SIZE);


    //************************************************************
    // Algorithme génétique pour trouver un bon réseau de neurone 
    //************************************************************
    for (int _generation = 0; _generation < GENERATION_COUNT; _generation++)
	{
        std::cout << "generation : " << _generation << std::endl;

        for (unsigned int i = 0; i < _pool.size(); i++)
        {
            // test avec le reseau de neurone
            _pool[i]->run(_fftOut, _generatorParam);

            // genere le son
            _generator.run(_generatorParam, _outGenerator, (float) _sampleWav.getSampleRate());

            // FFT du signal généré
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

        // croisement genetique entre les meilleurs réseaux de neurones
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

    // genere le son
    std::vector<short> _outputData(_inputWav.getSampleCount());
    std::vector<float> _previousGeneratorParam(GENERATOR_COUNT, 0.f);

    // le son est traité par morceau
    for (unsigned int i = 0; i < _inputWav.getSampleCount() - BUFFER_SIZE; i += BUFFER_SIZE)
    {
        for (unsigned int j = 0; j < BUFFER_SIZE; j++)
        {
            _fftIn[j].r = ((short*) _inputWav.getData())[i + j] / 32767.f;
            _fftIn[j].i = 0.f;
        }

        // fft
        kiss_fft(_fftCfg, _fftIn.data(), _fftOut.data());
        normalizeFFT(_fftOut);

        // réseau de neurone
        _pool[0]->run(_fftOut, _generatorParam);

        // générateurs
        _generator.run(_previousGeneratorParam, _generatorParam, _outGenerator, (float) _inputWav.getSampleRate(), i);
        _previousGeneratorParam = _generatorParam;

        // convertit en entier 16 bits
        for (unsigned int j = 0; j < BUFFER_SIZE; j++)
        {
            _outputData[i + j] = (short) (32767.f * _outGenerator[j].r);
        }
    }

    // écrit le son en sortie
    _inputWav.setSampleCount(_outputData.size());
    _inputWav.setData(_outputData.data(), _outputData.size() * sizeof(short));
    std::string _outFile = "out.wav";
    if (argc >= 4)
    {
        _outFile = argv[3];
    }
    std::cout << "write " << _outFile << std::endl;
    _inputWav.Write(_outFile.c_str());

	return EXIT_SUCCESS;
}
