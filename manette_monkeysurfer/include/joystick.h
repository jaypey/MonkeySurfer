#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "Arduino.h"
#include <stdlib.h>
#include <string.h>

const uint8_t PIN_JOYSTICK_X = A4;
const uint8_t PIN_JOYSTICK_Y = A5;
const uint16_t INITIAL_REPEAT_DELAY_JOYSTICK = 600;
const uint16_t REPEAT_DELAY_JOYSTICK = 200;

enum Direction {
    NEUTRE,
    HAUT,
    DROITE,
    BAS,
    GAUCHE
};

struct JoystickState {
    Direction direction;
    bool repetition;
};

class Joystick {
    private:
        uint8_t _pinX; // Broche analogique pour l'axe X
        uint8_t _pinY; // Broche analogique pour l'axe Y

        const int THRESHOLD_LEFT = 350;
        const int THRESHOLD_RIGHT = 650;
        const int THRESHOLD_DOWN = 350;
        const int THRESHOLD_UP = 650;

        Direction _lastDirectionX;
        Direction _lastDirectionY;
        unsigned long _lastRepeatX;
        unsigned long _lastRepeatY;
        bool _isInitialRepeatX;
        bool _isInitialRepeatY;
    public:
        Joystick();
        // Constructeur prenant les broches des axes X et Y en paramètre
        Joystick(uint8_t p_pinX, uint8_t p_pinY);
    
        // Fonction pour lire la direction de l'axe X du joystick
        Direction lireDirectionX();
    
        // Fonction pour lire la direction de l'axe Y du joystick
        Direction lireDirectionY();

        // Maintenu/appuye
        JoystickState getStateX();
        JoystickState getStateY();
};

#endif //JOYSTICK_H
