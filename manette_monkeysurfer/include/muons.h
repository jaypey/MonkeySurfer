#ifndef MUONS_H
#define MUONS_H

#include "Arduino.h"
#include <stdlib.h>
#include <string.h>
class DetecteurMuons
{
public:
    int detecteurDeMuons();
    int muons = 1;
    int derniermuons = 0;
};

#endif