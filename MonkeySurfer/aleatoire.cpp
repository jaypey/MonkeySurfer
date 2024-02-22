#include <iostream>
#include <string>
#include "aleatoire.h"

int RandomGenerator::random(int borneinf, int bornesup, int muons)
{
    int nbr;
    int modulo = abs(bornesup - borneinf);
    if (borneinf>bornesup)
    {
        int a = bornesup;
        bornesup = borneinf;
        borneinf = a;
    }
    nbr = (muons % (modulo+1))+borneinf;

    return nbr;
}