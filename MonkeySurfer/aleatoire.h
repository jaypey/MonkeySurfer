#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <iostream>
#include <string>

class RandomGenerator
{
public:
    int random(int borneinf, int bornesup, int muons);
    int verificateurNouveauMuon(int muons, int derniermuons);
    int derniermuons = 0;
    int muons = 1;
    int vraimuons = 1;
    int i = 0;
    int tableau[2];
};

#endif
