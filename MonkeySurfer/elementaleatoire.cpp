#include "elementaleatoire.h"

GenerateurItem::GenerateurItem()
{
}

GenerateurItem::~GenerateurItem()
{
}

ElementJeu* GenerateurItem::genererRandomElement()
{
	int valeurAleatoire = rand.random(0, 2, 451565);

	if (valeurAleatoire == 0)
	{
		return getRandomCollectible();
	}

	else if (valeurAleatoire == 1)
	{
		return getRandomObstacle();
	}

	return new Piece;
}

Collectible* GenerateurItem::getRandomCollectible()
{
	int valeurAleatoire = rand.random(0, 1, 95165);

	if (valeurAleatoire == 0)
	{
		return new Bouclier;
	}

	else if (valeurAleatoire == 1)
	{
		return new Banane;
	}

	return nullptr;
}

Obstacle* GenerateurItem::getRandomObstacle()
{
	int valeurAleatoire = rand.random(0, 1, 95165);

	if (valeurAleatoire == 0)
	{
		return new Projectile;
	}

	else if (valeurAleatoire == 1)
	{
		return new ObstacleFixe;
	}

	return nullptr;
}
