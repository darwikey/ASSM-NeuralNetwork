#pragma once


#include "stdafx.h"
#include "_kiss_fft_guts.h"

class NeuralNetwork;

class Neuron
{
public:
	Neuron(NeuralNetwork* fNeuralNetwork, int fInput);
	Neuron(NeuralNetwork* fNeuralNetwork, int fFirstInput, int fLastInput);


    //void findWeight(short* fBuffer, REAL fNeededOutput);

    REAL getOutput(const std::vector<kiss_fft_cpx>& fBuffer);

    void setWeight(REAL fW);


private:
	NeuralNetwork* mNeuralNetwork;

	std::list<structLink> mLinkList;
};

