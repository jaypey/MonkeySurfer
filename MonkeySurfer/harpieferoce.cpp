#include "harpieferoce.h"

HarpieFeroce::HarpieFeroce()
{
	direction = generateur.random(GAUCHE, DROITE, rand() % 1000);
	Coordonnee pos;

	pos.y = generateur.random(0, 20, rand() % 1000); //À changer pour la hauteur maximale de l'écran
	if (direction == GAUCHE)
	{
		pos.x = 4;
	}
	else
	{
		pos.x = 0;
	}

	setPosition(pos);

}

HarpieFeroce::~HarpieFeroce()
{
}

void HarpieFeroce::deplacement()
{
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
