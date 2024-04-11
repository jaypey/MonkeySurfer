#ifndef ELEMENTALEATOIRE_H
#define ELEMENTALEATOIRE_H

#include "banane.h"
#include "piece.h"
#include "bouclier.h"
#include "projectile.h"
#include "obstaclefixe.h"
#include "serpent.h"
#include "harpieferoce.h"
#include <random>
#include <jsonserial.h>

class GenerateurItem
{
public:
    GenerateurItem(JsonSerial* json);
    ~GenerateurItem();

    ElementJeu* getRandomElement();
    Collectible* getRandomCollectible();
    Obstacle* getRandomObstacle();

private:
    RandomGenerator rand;
    JsonSerial* _jsonSerial;
};

#endif // !ELEMENTALEATOIRE_H