#include "banane.h"

Banane::Banane()
{
	setID(BANANE);

	RandomGenerator rand;
	setDuree((float)rand.random(5, 9, 1951132));
}

Banane::~Banane()
{
}

void Banane::collision(Joueur& _joueur)
{
	stocker(_joueur);
}

void Banane::stocker(Joueur& joueur)
{
	joueur.ajouterInventaire(this);
	if (joueur.getNbItem() == 1)
	{
		joueur.setCharInventaire({ 'B', ' ' });
	}
	else if (joueur.getNbItem() == 2)
	{
		joueur.setCharInventaire({ joueur.getCharInventaire().item1, 'B' });
	}
}

void Banane::appliquerEffet(Joueur& joueur)
{
	joueur.setEtatEffetBanane(true);
	joueur.setCharInventaire({ joueur.getCharInventaire().item2, ' ' });
	lastUpdateBanane = std::chrono::steady_clock::now();
}

void Banane::afficherInfo() const
{
	std::cout << "Banane attrapée!!!" << std::endl;
}
