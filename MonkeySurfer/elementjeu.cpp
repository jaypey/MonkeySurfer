#include "elementjeu.h"
#include <chrono>

ElementJeu::ElementJeu()
{
	id = -1;
	position = { 0, 0 };
}

ElementJeu::~ElementJeu()
{
}

int ElementJeu::getID()
{
	return id;
}

void ElementJeu::setID(int p_id)
{
	id = p_id;
}

Coordonnee ElementJeu::getPosition()
{
	return position;
}

void ElementJeu::setPosition(Coordonnee p_position)
{
	position = p_position;
}
