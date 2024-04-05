#include "harpieferoce.h"

HarpieFeroce::HarpieFeroce()
{
	setID(HARPIE);
	if (generateur.random(0, 1, rand() % 1000))
	{
		direction = GAUCHE;
	}
	else
	{
		direction = DROITE;
	}
	Coordonnee pos;

	pos.y = generateur.random(0, 20, rand() % 1000); // A changer pour la hauteur maximale de l'ecran
	if (direction == GAUCHE)
	{
		pos.x = 4;
	}
	else
	{
		pos.x = 0;
	}

	setPosition(pos);
	avertissement = true;
}

HarpieFeroce::~HarpieFeroce()
{
}

void HarpieFeroce::deplacement()
{
	if (avertissement) {
		avertissement = false;
		return;
	}

	if (direction == GAUCHE)
	{
		setPosition({ getPosition().x - 1, getPosition().y });
	}
	else
	{
		setPosition({ getPosition().x + 1, getPosition().y });
	}
}

int HarpieFeroce::getDirection()
{
	return direction;
}

bool HarpieFeroce::getAvertissement() {
	return avertissement;
}

bool HarpieFeroce::collision(Joueur& _joueur)
{
	if (avertissement)
		return false;

	if (_joueur.getEtatBouclier())
	{
		_joueur.setEtatBouclier(false);   // Desactive le bouclier
	}
	else
	{
		_joueur.isDead();
	}
	delete this;
	return true;
}

bool HarpieFeroce::finDeParcours()
{
	if ((getDirection() == GAUCHE && getPosition().x == 0) ||
		getDirection() == DROITE && getPosition().x == 4)
	{
		return true;
	}
	return false;
}

void HarpieFeroce::afficherInfo() const
{
	std::cout << "Une harpie feroce est apparu" << std::endl;
}
