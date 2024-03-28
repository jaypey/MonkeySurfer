#include "banane.h"

Banane::Banane()
{
	setID(BANANE);
	setPosition({ generateur.random(0, 4, std::rand() % 1000), 0 });
	RandomGenerator rand;
	setDuree((float)rand.random(5, 9, std::rand() % 1000));
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
	joueur.setNbBoost(generateur.random(3, 6, std::rand() % 299));
	joueur.setCharInventaire({ joueur.getCharInventaire().item2, ' ' });
}

void Banane::afficherInfo() const
{
	std::cout << "Banane attrapée!!!" << std::endl;
}



