#include "stdafx.h"
#include "NeuralNetwork.h"
#include "kiss_fft.h"
#include "Generator.h"



// Constructeur réseau de neurones
NeuralNetwork::NeuralNetwork() : mNumInput(BUFFER_SIZE/2), mNumOutput(GENERATOR_COUNT)
{
    for (int i = 0; i < mNumOutput; i++)
    {
        std::vector<float> _weights(mNumInput, 0.f);

        /*for (int j = 0; j < mNumInput; j++)
        {

        }*/
        _weights[random(0, mNumInput)] = 0.2f;
        _weights[random(0, mNumInput)] = 1.f;

        mNeuronArray.push_back(_weights);
    }
}


// croisement entre deux parents
NeuralNetwork::NeuralNetwork(const NeuralNetwork* fParent1, const NeuralNetwork* fParent2) : mNumInput(BUFFER_SIZE/2), mNumOutput(GENERATOR_COUNT)
{
    for (int i = 0; i < mNumOutput; i++)
    {
        std::vector<float> _weights(mNumInput);
        int _swap = random(0, mNumInput);

        for (int j = 0; j < mNumInput; j++)
        {
            if (j < _swap)
            {
                _weights[j] = fParent1->mNeuronArray[i][j];
            }
            else
            {
                _weights[j] = fParent2->mNeuronArray[i][j];
            }
        }

        mNeuronArray.push_back(_weights);
    }
}


void NeuralNetwork::run(const std::vector<kiss_fft_cpx>& fInput, std::vector<float>& fOut)
{
    for (int i = 0; i < (int)fOut.size(); i++)
    {
        float _out = 0.f;

        for (int j = 0; j < mNumInput; j++)
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


void NeuralNetwork::debug()
{
    for (int i = 0; i < mNumOutput; i++)
    {
        for (int j = 0; j < mNumInput / 2; j++)
        {
            std::cout << (int)(mNeuronArray[i][j] * 5000.f) << " ";
        }
        std::cout << std::endl;
    }
}