#ifndef BANANE_H
#define BANANE_H

#include "collectible.h"

class Banane : public Collectible
{
public:
	Banane();
	~Banane();

	virtual void collision(Joueur& _joueur);
	virtual void stocker(Joueur& joueur);
	virtual void appliquerEffet(Joueur& joueur);
	virtual void afficherInfo() const;

private:
	std::chrono::steady_clock::time_point lastUpdateBanane;
};

#endif // !BANANE_H

