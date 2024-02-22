#include "banane.h"

Banane::Banane()
{
	setID(BANANE);

	RandomGenerator rand;
	setDuree(rand.random(5, 9, 1951132));
}

Banane::~Banane()
{
}

void Banane::stocker(Joueur& joueur)
{
	//ajoute une banane dans l'inventairedu joueur
}

void Banane::appliquerEffet(Joueur& joueur)
{
	//active la possibilité pendant x secondes (var duree) du double saut chez le joueur
}

void Banane::afficherInfo() const
{
	std::cout << "Banane attrapée!!!" << std::endl;
}
