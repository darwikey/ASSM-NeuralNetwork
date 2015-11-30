#pragma once


#include "stdafx.h"

class NeuralNetwork;

class Neurone
{
public:
	Neurone(NeuralNetwork* fNeuralNetwork, int fEntree);
	Neurone(NeuralNetwork* fNeuralNetwork, int fPremiere_entree, int fDerniere_entree);


	void findWeight(Pomme& fPomme, long double fSortie_voulue);

	long double getSortie(Pomme& fPomme);



private:
	NeuralNetwork* m_NeuralNetwork;

	std::list<struct_lien> m_list_lien;
};

