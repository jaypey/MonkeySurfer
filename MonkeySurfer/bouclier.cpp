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
}

void Bouclier::appliquerEffet(Joueur& joueur)
{
	joueur.setEtatBouclier(true);
	lastUpdateBouclier = std::chrono::steady_clock::now();
}

void Bouclier::afficherInfo() const
{
	std::cout << "Bouclier activé" << std::endl;
}
