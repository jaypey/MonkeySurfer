#include "joueur.h"

Joueur::Joueur()
{
	position = { 2, 15 };
}

Joueur::~Joueur()
{
}

Coordonnee Joueur::getPosition()
{
	return position;
}

void Joueur::setPosition(Coordonnee c)
{
	position = c;
}
