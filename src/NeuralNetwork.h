#pragma once


#include "stdafx.h"
#include <fstream>



class NeuralNetwork
{
public:
	NeuralNetwork();
    NeuralNetwork(const NeuralNetwork* fParent1, const NeuralNetwork* fParent2);

    void run(const std::vector<kiss_fft_cpx>& fData, vector<float>& fOut);

    void debug();

    float mScore = 0.f;

    static bool sortFct(const NeuralNetwork* a, const NeuralNetwork* b);

private:
	int mNumInput;
	int mNumOutput;

    std::vector<std::vector<float>> mNeuronArray;

};