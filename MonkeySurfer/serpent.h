#ifndef SERPENT_H
#define SERPENT_H
#include "obstacle.h"

class Serpent : public Obstacle
{
public:
	Serpent();
	~Serpent();
	void attraperJoueur(Joueur& p_joueur);
	int getHp();
	void recoitCoup();
	void mourir();

private:
	int hp;

};

#endif //SERPENT_H