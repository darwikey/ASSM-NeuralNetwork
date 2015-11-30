#pragma once


#include "stdafx.h"

class NeuralNetwork;

class Neuron
{
public:
	Neuron(NeuralNetwork* fNeuralNetwork, int fInput);
	Neuron(NeuralNetwork* fNeuralNetwork, int fFirstInput, int fLastInput);


    //void findWeight(short* fBuffer, long double fNeededOutput);

    long double getOutput(short* fBuffer);

    void setWeight(long double fW);


private:
	NeuralNetwork* mNeuralNetwork;

	std::list<structLink> mLinkList;
};

