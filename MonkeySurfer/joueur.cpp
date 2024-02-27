#include "joueur.h"

Joueur::Joueur()
{
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
