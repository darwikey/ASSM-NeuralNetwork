#pragma once


#include "stdafx.h"
#include <fstream>



class NeuralNetwork
{
public:
	NeuralNetwork(int fNumInput);


    REAL getInput(int fInput, const std::vector<kiss_fft_cpx>& fBuffer);
    void findWeight();

    void run(const std::vector<kiss_fft_cpx>& fData, vector<float>& fOut);

	std::vector<Neuron*> mNeuronArray;

    float mScore = 0.f;

    static bool sortFct(const NeuralNetwork* a, const NeuralNetwork* b);

private:
	int mNumInput;
	int mNumOutput;
};