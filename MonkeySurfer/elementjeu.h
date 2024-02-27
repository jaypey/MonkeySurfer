#ifndef ELEMENTJEU_H
#define ELEMENTJEU_H

#include <iostream>
#include "joueur.h"
#include "aleatoire.h"
#include "coordonnee.h"

#define OBSTACLE_FIXE		0
#define OBSTACLE_TOMBANT	1
#define BANANE				2
#define BOUCLIER			3
#define PIECE				4

#define HAUTEUR_GENERATION	11

class ElementJeu
{
public:
	ElementJeu();
	virtual ~ElementJeu();

	virtual void afficherInfo() const = 0;

	int getID();
	void setID(int p_id);

	Coordonnee getPosition();
	void setPosition(Coordonnee);

protected:
	RandomGenerator generateur;

private:
	int id;
	Coordonnee position;
};

#endif // !ELEMENTJEU_H

