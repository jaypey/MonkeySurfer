#include "collectible.h"

Collectible::Collectible()
{
    duree = 0;
    etat = true;
}

Collectible::~Collectible()
{
}

float Collectible::getDuree()
{
    return duree;
}

void Collectible::setDuree(float p_duree)
{
    duree = p_duree;
}

bool Collectible::getEtat()
{
    return etat;
}

void Collectible::setEtat(bool p_etat)
{
    etat = p_etat;
}

