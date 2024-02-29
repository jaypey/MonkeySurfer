#ifndef BOUTON_H
#define BOUTON_H

#include "Arduino.h"
#include <stdlib.h>
#include <string.h>

const uint8_t PIN_BTN_1 = 2;
const uint8_t PIN_BTN_2 = 3;
const uint8_t PIN_BTN_3 = 4;
const uint8_t PIN_BTN_4 = 5;

class Bouton {
    private:
        uint8_t pinBtn[4];
    
    public:
        Bouton();
        // Constructeur prenant les broches des boutons en paramètre
        Bouton(uint8_t p_pinBtn1, uint8_t p_pinBtn2, uint8_t p_pinBtn3, uint8_t p_pinBtn4);
    
        // Fonctions pour lire l'état des boutons
        bool lireBouton(int i);
};

#endif //BOUTON_H