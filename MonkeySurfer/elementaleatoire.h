#ifndef ELEMENTALEATOIRE_H
#define ELEMENTALEATOIRE_H

#include "banane.h"
#include "piece.h"
#include "bouclier.h"
#include "projectile.h"
#include "obstaclefixe.h"
#include "serpent.h"
#include "harpieferoce.h"

class GenerateurItem
{
public:
	GenerateurItem();
	~GenerateurItem();

	ElementJeu* genererRandomElement();
	Collectible* getRandomCollectible();
	Obstacle* getRandomObstacle();

private:
	RandomGenerator rand;
};

#endif // !ELEMENTALEATOIRE_H