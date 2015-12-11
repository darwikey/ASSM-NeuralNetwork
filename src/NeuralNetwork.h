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


private:
	int mNumInput;
	int mNumOutput;
};