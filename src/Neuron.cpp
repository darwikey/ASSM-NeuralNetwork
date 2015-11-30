#include "stdafx.h"
#include "Neuron.h"
#include "NeuralNetwork.h"
#include "WAV.h"


// Pour les neurones en entrée
Neurone::Neurone(NeuralNetwork* fNeuralNetwork, int fEntree) : m_NeuralNetwork(fNeuralNetwork)
{
	struct_lien _lien;
	_lien.id_entree = fEntree;
	_lien.poids = 0;

	m_list_lien.push_back(_lien);
}


// Constructeur générique
Neurone::Neurone(NeuralNetwork* fNeuralNetwork, int fPremiere_entree, int fDerniere_entree) : m_NeuralNetwork(fNeuralNetwork)
{
	// On connecte les entrées
	for (int i=fPremiere_entree; i<=fDerniere_entree; i++)
	{
		struct_lien _lien;
		_lien.id_entree = i;

		// on donne un poids aléatoire
		_lien.poids = random(-.001L, .001L);

		m_list_lien.push_back(_lien);
	}
}


// A partir des entrés/sorties et de la sortie voulue, on calcule les poids des entrées
void Neurone::findWeight(Pomme& fPomme, long double fSortie_voulue)
{
	long double _sortie_reel = this->getSortie(fPomme);
	
	for (auto it=m_list_lien.begin(); it!=m_list_lien.end(); ++it)
	{
		Neurone* _neurone_liee = m_NeuralNetwork->m_tab_neurone[it->id_entree];
		
		long double _entree = _neurone_liee->getSortie(fPomme);

		const float _pas = 0.00000001L;

		// compensation à ajouter
		long double _delta = _pas * (fSortie_voulue - _sortie_reel) * _entree;

		it->poids += _delta;
	}
}


// Calcul la sortie du neurone
long double Neurone::getSortie(Pomme& fPomme)
{
	if (m_list_lien.size() == 0)
	{
		return 0.L;
	}
	else if (m_list_lien.size() == 1 && m_list_lien.front().id_entree < 0)
	{
		return m_NeuralNetwork->getEntree(-1 -m_list_lien.front().id_entree, fPomme);
	}
	else
	{

		long double _somme = 0;
		for (auto it=m_list_lien.begin(); it!=m_list_lien.end(); ++it)
		{
			Neurone* _neurone_liee = m_NeuralNetwork->m_tab_neurone[it->id_entree];
			long double _entree = _neurone_liee->getSortie(fPomme);

			_somme += it->poids * _entree;
		}


		return _somme;
	}
}