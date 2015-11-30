#include "stdafx.h"
#include "Neuron.h"
#include "NeuralNetwork.h"
#include "time.h"
#include "WAV.h"



int main(int argc, char *argv[])
{
	//Initialisation 
	std::cout << "INIT" << std::endl;
	srand((int)time(NULL));


	//Reseau
	NeuralNetwork* _network = new NeuralNetwork(1000);


	
	float _timespan = 0.2f;
	std::vector<WAV> _retval;
	WAV _wav;
	_wav.Read("data/test.wav");
	if (_wav.empty())
	{
		std::cout << "unable to open file" << std::endl;
		return EXIT_FAILURE;
	}

	unsigned int _endBytePos = _wav.getSampleCount() * _wav.getChannels() * (_wav.getBit() / 8);

	char* _outputData = new char[_endBytePos];

	for (int i = 0; i < _endBytePos; i += 1024)
	{


		// envoyer dans le reseau
		//_reseau->findWeight(*_pomme);
	}



	return 0;
}


// Constructeur réseau de neurones
NeuralNetwork::NeuralNetwork(int fNb_entree) : mNumInput(fNb_entree)
{
	mNumOutput = 3;

	//entrée
	for (int i=0; i<=mNumInput-1; i++)
	{
		Neurone* _neurone = new Neurone(this, -i-1);
		m_tab_neurone.push_back(_neurone);
	}

	// sortie
	for (int i=mNumInput; i <= mNumInput +mNumOutput -1; i++)
	{
		Neurone* _neurone = new Neurone(this, 0, mNumInput-1);
		m_tab_neurone.push_back(_neurone);
	}

	//fichier
	mFile.open("resultat.txt");
	mFile.clear();
}


// Renvoie l'entrée
long double NeuralNetwork::getEntree(int fEntree, Pomme& fPomme)
{
	if (fEntree<1000)
		return (long double)fPomme.m_couleur[fEntree];
	else
		return 0.L;
}


// Calcul les poids des neurones 
void NeuralNetwork::findWeight(Pomme& fpomme)
{
	
	Neurone* _neurone = m_tab_neurone[mNumInput];

	long double _sortie = _neurone->getSortie(fpomme);
	printf("%4.4f    ", _sortie);


	static int _cycle = 0;
	static int _resultat = 0;

	if (fpomme.m_tachete > 0) // tacheté
	{
		if (_sortie > 0.5L)
			_resultat ++; // bonne sortie

	}
	else // pas tacheté
	{
		if (_sortie < 0.5L)
			_resultat ++; // bonne sortie

	}
	

	// on met les resultats dans un fichier texte
	_cycle ++;
	if (_cycle >= 20)
	{
		_cycle = 0;

		mFile<<_resultat<<endl;

		_resultat = 0;
	}


	_neurone->findWeight(fpomme, (long double)fpomme.m_tachete / 4.L);

	
}


