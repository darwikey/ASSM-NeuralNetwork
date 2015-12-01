#pragma once


#include "stdafx.h"

class NeuralNetwork;

class Neuron
{
public:
	Neuron(NeuralNetwork* fNeuralNetwork, int fInput);
	Neuron(NeuralNetwork* fNeuralNetwork, int fFirstInput, int fLastInput);


    //void findWeight(short* fBuffer, REAL fNeededOutput);

    REAL getOutput(short* fBuffer);

    void setWeight(REAL fW);


private:
	NeuralNetwork* mNeuralNetwork;

	std::list<structLink> mLinkList;
};

