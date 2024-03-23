#include "serpent.h"

Serpent::Serpent()
{
	hp = generateur.random(6, 10, rand() % 1000);
}

Serpent::~Serpent()
{
}

void Serpent::collision(Joueur& _joueur)
{
	attraperJoueur(_joueur);
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

void Serpent::afficherInfo() const
{
	std::cout << "Un serpent est apparu" << std::endl;
}