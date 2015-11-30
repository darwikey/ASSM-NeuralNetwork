#include "stdafx.h"
#include "Neuron.h"
#include "NeuralNetwork.h"
#include "time.h"
#include "WAV.h"
#include <algorithm>



int main(int argc, char *argv[])
{
	//Initialisation 
	std::cout << "INIT" << std::endl;
	srand((int)time(NULL));


	//Reseau
	NeuralNetwork _network (BUFFER_SIZE);
   


	WAV _inputWav, _sampleWav;
	
    if (_inputWav.Read("data/sum41.wav") || _sampleWav.Read("data/sum41.wav"))
	{
		return EXIT_FAILURE;
	}

    if (_inputWav.getChannels() != 1 || _sampleWav.getChannels() != 1)
    {
        cerr << "stereo sounds are not supported" << endl;
        return EXIT_FAILURE;
    }

    short _sampleBuffer[BUFFER_SIZE];
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        _sampleBuffer[i] = ((short*)_sampleWav.getData())[i];
    }

    _network.findWeight(_sampleBuffer);


	int _endBytePos = _inputWav.getSampleCount();

    const short* _inputData = (short*) _inputWav.getData();
	short* _outputData = new short[_endBytePos];

	for (int i = 0; i + BUFFER_SIZE < _endBytePos; i ++)
	{
        _outputData[i] = _inputData[i];


	}

    _inputWav.setData(_outputData, _inputWav.getDataSize());
    cout << "write out.wav" << endl;
    _inputWav.Write("out.wav");

	return 0;
}


// Constructeur réseau de neurones
NeuralNetwork::NeuralNetwork(int fNumInput) : mNumInput(fNumInput)
{
	mNumOutput = 1;

	//entrée
	for (int i=0; i<mNumInput; i++)
	{
		Neuron* _neuron = new Neuron(this, -i-1);
		mNeuronArray.push_back(_neuron);
	}

	// sortie
	for (int i=mNumInput; i < mNumInput +mNumOutput; i++)
	{
		Neuron* _neuron = new Neuron(this, 0, mNumInput-1);
		mNeuronArray.push_back(_neuron);
	}
}


// Renvoie l'entrée
long double NeuralNetwork::getInput(int fInput, short* fBuffer)
{
	if (fInput < BUFFER_SIZE)
		return (long double)fBuffer[fInput];
	else
		return 0.L;
}


// Calcul les poids des neurones 
void NeuralNetwork::findWeight(short* fBuffer)
{
	
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        mNeuronArray[i]->setWeight(fBuffer[i]);
    }
	
}


