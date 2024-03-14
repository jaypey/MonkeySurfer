#include "serpent.h"

Serpent::Serpent()
{
	hp = generateur.random(6, 10, rand() % 1000);
}

Serpent::~Serpent()
{
}

void Serpent::attraperJoueur(Joueur& p_joueur)
{
	p_joueur.immobiliser(true);
}

int Serpent::getHp()
{
	return hp;
}

void Serpent::recoitCoup(Joueur& p_joueur)
{
	hp--;
	if (hp <= 0)
	{
		mourir(p_joueur);
	}
}

void Serpent::mourir(Joueur& p_joueur)
{
	p_joueur.immobiliser(false);
	//this->~Serpent();
}
