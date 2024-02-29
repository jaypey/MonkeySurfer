#ifndef MOTEURVIBRANT_H
#define MOTEURVIBRANT_H

#include "Arduino.h"
#include <stdlib.h>
#include <string.h>

const uint8_t PIN_MOTEUR_VIBRANT = 6;

class MoteurVibrant {
  private:
    int pinMoteur; // Broche pour le moteur vibrant
    
  public:
    MoteurVibrant();
    // Constructeur prenant la broche du moteur vibrant en paramètre
    MoteurVibrant(int p_pinMoteur);
    
    // Fonction pour contrôler l'état du moteur vibrant (HIGH pour l'allumer, LOW pour l'éteindre)
    void controlerMoteur(int etat);
};

#endif //MOTEURVIBRANT_H