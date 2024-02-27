#include "coordonnee.h"
#ifndef JOUEUR_H
#define JOUEUR_H

class Joueur
{
public:
	Joueur();
	~Joueur();

	Coordonnee getPosition();
	void setPosition(Coordonnee);
private:
	Coordonnee position;
};

#endif // !JOUEUR_H
