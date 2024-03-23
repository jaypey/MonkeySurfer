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

	switch (valeurAleatoire)
	{
	case 0:
		return new Bouclier;

	case 1:
		return new Banane;

	default:
		break;
	}

	return nullptr;
}

Obstacle* GenerateurItem::getRandomObstacle()
{
	int valeurAleatoire = rand.random(0, 1, 95165);

	switch (valeurAleatoire)
	{
	case 0:
		return new ObstacleFixe;

	case 1:
		return new ObstacleFixe;

	case 2:
		return new Serpent;

	default:
		break;
	}

	return nullptr;
}
