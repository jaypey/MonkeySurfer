#ifndef BOUTON_H
#define BOUTON_H

#include "Arduino.h"
#include <stdlib.h>
#include <string.h>

struct BoutonState {
    bool maintenu;
    bool appuye;
};

class Bouton {
private:
    uint8_t _pinBtn[4];
    bool _dejaAppuye[4]; // bouton est maintenu depuis longtemps

public:
    // Constructeur prenant les broches des boutons en paramètre
    Bouton(uint8_t p_pinBtn1, uint8_t p_pinBtn2, uint8_t p_pinBtn3, uint8_t p_pinBtn4);

    // Fonctions pour lire l'état des boutons
    BoutonState getState(int i);
};

#endif // BOUTON_H!
