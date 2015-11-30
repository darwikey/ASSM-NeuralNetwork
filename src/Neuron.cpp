#include "stdafx.h"
#include "Neuron.h"
#include "NeuralNetwork.h"
#include "WAV.h"


// Pour les neurones en entrée
Neuron::Neuron(NeuralNetwork* fNeuralNetwork, int fInput) : mNeuralNetwork(fNeuralNetwork)
{
    structLink _link;
    _link.idInput = fInput;
    _link.weight = 0;

    mLinkList.push_back(_link);
}


// Constructeur générique
Neuron::Neuron(NeuralNetwork* fNeuralNetwork, int fFirstInput, int fLastInput) : mNeuralNetwork(fNeuralNetwork)
{
	// On connecte les entrées
	for (int i=fFirstInput; i<=fLastInput; i++)
	{
		structLink _link;
        _link.idInput = i;

		// on donne un poids 
        _link.weight = 1.L / (fLastInput - fFirstInput);//random(-.001L, .001L);

        mLinkList.push_back(_link);
	}
}


// A partir des entrés/sorties et de la sortie voulue, on calcule les poids des entrées
/*void Neuron::findWeight(short* fBuffer, long double fNeededOutput)
{
	long double _realOutput = this->getOutput(fBuffer);
	
	for (auto it=mLinkList.begin(); it!=mLinkList.end(); ++it)
	{
        Neuron* _linkedNeuron = mNeuralNetwork->mNeuronArray[it->idInput];
		
		long double _input = _linkedNeuron->getOutput(fBuffer);

		const float _step = 0.00000001L;

		// compensation à ajouter
        long double _delta = _step * (fNeededOutput - _realOutput) * _input;

		it->weight += _delta;
	}
}*/


// Calcul la sortie du neurone
long double Neuron::getOutput(short* fBuffer)
{
	if (mLinkList.size() == 0)
	{
		return 0.L;
	}
	else if (mLinkList.size() == 1 && mLinkList.front().idInput < 0)
	{
		return mNeuralNetwork->getInput(-1 -mLinkList.front().idInput, fBuffer);
	}
	else
	{

		long double _sum = 0;
		for (auto it=mLinkList.begin(); it!=mLinkList.end(); ++it)
		{
			Neuron* _Neuron_liee = mNeuralNetwork->mNeuronArray[it->idInput];
			long double _Input = _Neuron_liee->getOutput(fBuffer);

			_sum += it->weight * _Input;
		}


		return _sum;
	}
}


void Neuron::setWeight(long double fW)
{
    for (auto it = mLinkList.begin(); it != mLinkList.end(); ++it)
    {
        it->weight = fW;
    }
}