#ifndef BANANE_H
#define BANANE_H

#include "collectible.h"

class Banane : public Collectible
{
public:
	Banane();
	~Banane();

	void stocker(Joueur& joueur);
	void appliquerEffet(Joueur& joueur);
	void afficherInfo() const;

};

#endif // !BANANE_H

