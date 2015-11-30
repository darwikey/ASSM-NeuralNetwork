#pragma once


#include "stdafx.h"
#include <fstream>

class Pomme;

class NeuralNetwork
{
public:
	NeuralNetwork(int fNb_entree);


	long double getEntree(int fInput, Pomme& fPomme);
	void findWeight(Pomme& fpomme);

	std::vector<Neurone*> m_tab_neurone;


private:
	int mNumInput;
	int mNumOutput;


	// fichier texte de sortie
	ofstream mFile;
};