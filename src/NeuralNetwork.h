#pragma once


#include "stdafx.h"
#include <fstream>



class NeuralNetwork
{
public:
	NeuralNetwork(int fNumInput);


    REAL getInput(int fInput, short* fBuffer);
    void findWeight(short* fBuffer);

    REAL test(short* fData, int fStart, int fEnd);

	std::vector<Neuron*> mNeuronArray;


private:
	int mNumInput;
	int mNumOutput;
};