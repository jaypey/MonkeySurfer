#ifndef ELEMENTJEU_H
#define ELEMENTJEU_H

#include <iostream>
#include "joueur.h"
#include "aleatoire.h"

#define OBSTACLE_FIXE		0
#define OBSTACLE_TOMBANT	1
#define BANANE				2
#define BOUCLIER			3
#define PIECE				4

class ElementJeu
{
public:
	ElementJeu();
	virtual ~ElementJeu();

	virtual void afficherInfo() const = 0;

	int getID();
	void setID(int p_id);

private:
	int id;
};

#endif // !ELEMENTJEU_H

