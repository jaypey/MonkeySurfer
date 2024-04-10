#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <iostream>
#include <string>

class RandomGenerator
{
public:
    int random(int borneinf, int bornesup, int muons);
    void verificateurNouveauMuon(int muons, int derniermuons);
};

#endif
