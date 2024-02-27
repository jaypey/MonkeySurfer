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
	//ajouter un bouclier dans l'inventaire du joueur
}

void Bouclier::appliquerEffet(Joueur& joueur)
{
	//activer le bouclier pendant x secondes (var duree) dans la classe joueur
}

void Bouclier::afficherInfo() const
{
	std::cout << "Bouclier activé" << std::endl;
}
