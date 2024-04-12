#include "elementaleatoire.h"

GenerateurItem::GenerateurItem(JsonSerial* json)
{
    _jsonSerial = json;
}

GenerateurItem::~GenerateurItem()
{
}

ElementJeu* GenerateurItem::getRandomElement()
{
    int valeurAleatoire = rand.random(0, 10, std::rand() % 500);

    if (valeurAleatoire < 4)
    {
        return getRandomCollectible();
    }

    else
    {
        return getRandomObstacle();
    }

}

Collectible* GenerateurItem::getRandomCollectible()
{
    int valeurAleatoire = _jsonSerial->muons(&rand, 0, 1);
    if (valeurAleatoire == -1)
    {
        valeurAleatoire = rand.random(0, 1, std::rand()%500);
    }
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
    int valeurAleatoire = _jsonSerial->muons(&rand, 0, 2);
    if (valeurAleatoire == -1)
    {
        valeurAleatoire = rand.random(0, 2, std::rand() % 500);
    }

    switch (valeurAleatoire)
    {
    case 0:
        return new ObstacleFixe;

    case 1:
        return new HarpieFeroce;

    case 2:
        return new Serpent;

    default:
        break;
    }

    return nullptr;
}
