#pragma once


#include "stdafx.h"
#include <fstream>



class NeuralNetwork
{
public:
	NeuralNetwork(int fNumInput);


    long double getInput(int fInput, short* fBuffer);
    void findWeight(short* fBuffer);

	std::vector<Neuron*> mNeuronArray;


private:
	int mNumInput;
	int mNumOutput;
};