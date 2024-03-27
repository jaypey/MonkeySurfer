#include "bouclier.h"


Bouclier::Bouclier()
{
	setID(BOUCLIER);
	
	RandomGenerator rand;
	setDuree((float)rand.random(10, 15, 2543312));
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
	joueur.setEtatBouclier(true);
	joueur.setCharInventaire({ joueur.getCharInventaire().item2, ' ' });
	lastUpdateBouclier = std::chrono::steady_clock::now();
}

void Bouclier::afficherInfo() const
{
	std::cout << "Bouclier activé" << std::endl;
}
