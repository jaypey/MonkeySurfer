#include "bouton.h"

Bouton::Bouton(uint8_t pinBtn1, uint8_t pinBtn2, uint8_t pinBtn3, uint8_t pinBtn4)
{
    _pinBtn[0] = pinBtn1;
    _pinBtn[1] = pinBtn2;
    _pinBtn[2] = pinBtn3;
    _pinBtn[3] = pinBtn4;

    // Configuration des broches des boutons en entrée avec une résistance de pull-up activée
    for (int i = 0; i < 4; ++i) {
        pinMode(_pinBtn[i], INPUT);
        _dejaAppuye[i] = false;
    }
}

BoutonState Bouton::getState(int i)
{
    BoutonState bstate;
    bstate.maintenu = !digitalRead(_pinBtn[i]);

    bstate.appuye = (bstate.maintenu && !_dejaAppuye[i]);
    _dejaAppuye[i] = bstate.maintenu;

    return bstate;
}
