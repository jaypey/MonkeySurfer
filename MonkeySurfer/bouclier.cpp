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

void Bouclier::stocker(Joueur& joueur)
{
	joueur.ajouterInventaire(getID());
}

void Bouclier::appliquerEffet(Joueur& joueur)
{
	joueur.changerEtatBouclier(true);
}

void Bouclier::afficherInfo() const
{
	std::cout << "Bouclier activé" << std::endl;
}
