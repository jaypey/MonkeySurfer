#include "bouclier.h"


Bouclier::Bouclier()
{
	setID(BOUCLIER);
	setPosition({ generateur.random(0, 4, std::rand() % 1000), 0 });
	RandomGenerator rand;
	setDuree((float)rand.random(10, 15, std::rand() % 500));
}

Bouclier::~Bouclier()
{
}

void Bouclier::collision(Joueur& _joueur)
{
	stocker(_joueur);
}

void Bouclier::stocker(Joueur& joueur)
{
	joueur.ajouterInventaire(this);
	if (joueur.getNbItem() == 1 )
	{
		joueur.setCharInventaire({ '@', ' '});
	}
	else if (joueur.getNbItem() == 2)
	{
		joueur.setCharInventaire({ joueur.getCharInventaire().item1, '@' });
	}
}

void Bouclier::appliquerEffet(Joueur& joueur)
{	
	if (joueur.isFree()) {
		joueur.setEtatBouclier(true);
	}
	else {
		joueur.immobiliser(false);
	}
	joueur.setCharInventaire({ joueur.getCharInventaire().item2, ' ' });
	lastUpdateBouclier = std::chrono::steady_clock::now();
}

void Bouclier::afficherInfo() const
{
	std::cout << "Bouclier activé" << std::endl;
}
