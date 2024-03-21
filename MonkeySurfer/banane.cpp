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
}

void Banane::appliquerEffet(Joueur& joueur)
{
	joueur.setEtatEffetBanane(true);
	lastUpdateBanane = std::chrono::steady_clock::now();
}

void Banane::afficherInfo() const
{
	std::cout << "Banane attrapée!!!" << std::endl;
}
