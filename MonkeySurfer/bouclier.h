#ifndef BOUCLIER_H
#define BOUCLIER_H
#include "collectible.h"

class Bouclier : public Collectible
{
public:
	Bouclier();
	~Bouclier();

	void stocker(Joueur& joueur);
	void appliquerEffet(Joueur& joueur);
	void afficherInfo() const;
};

#endif // !BOUCLIER_H
