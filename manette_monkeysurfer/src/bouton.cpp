#include "bouton.h"

Bouton::Bouton() 
{
    this->pinBtn[0] = PIN_BTN_1;
    this->pinBtn[1] = PIN_BTN_2;
    this->pinBtn[2] = PIN_BTN_3;
    this->pinBtn[3] = PIN_BTN_4;
    
    // Configuration des broches des boutons en entrée avec une résistance de pull-up activée
    for (int i = 0; i < 4; ++i) {
        pinMode(pinBtn[i], INPUT);
    }
}

Bouton::Bouton(uint8_t p_pinBtn1, uint8_t p_pinBtn2, uint8_t p_pinBtn3, uint8_t p_pinBtn4) 
{
    this->pinBtn[0] = p_pinBtn1;
    this->pinBtn[1] = p_pinBtn2;
    this->pinBtn[2] = p_pinBtn3;
    this->pinBtn[3] = p_pinBtn4;
    
    // Configuration des broches des boutons en entrée avec une résistance de pull-up activée
    for (int i = 0; i < 4; ++i) {
        pinMode(pinBtn[i], INPUT);
    }
}

bool Bouton::lireBouton(int i)
{
    return !digitalRead(pinBtn[i]);
}