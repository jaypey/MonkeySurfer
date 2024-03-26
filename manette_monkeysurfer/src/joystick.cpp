#include "joystick.h"

Joystick::Joystick() 
{
    _pinX = PIN_JOYSTICK_X;
    _pinY = PIN_JOYSTICK_Y;
    _lastDirectionX = NEUTRE;
    _lastDirectionY = NEUTRE;
}

Joystick::Joystick(uint8_t p_pinX, uint8_t p_pinY) 
{
    _pinX = p_pinX;
    _pinY = p_pinY;
    _lastDirectionX = NEUTRE;
    _lastDirectionY = NEUTRE;
}

Direction Joystick::lireDirectionX()
{
    // Lecture de la valeur de l'axe X du joystick
    int valeurX = analogRead(_pinX);

    // Retourner "Gauche" si la valeur est supérieur à 350, sinon "Droite"
    if (valeurX < THRESHOLD_LEFT)
        return DROITE;
    else if (valeurX > THRESHOLD_RIGHT)
        return GAUCHE;
    return NEUTRE;
}

Direction Joystick::lireDirectionY()
{
    // Lecture de la valeur de l'axe X du joystick
    int valeurY = analogRead(_pinY);
    
    // Retourner "Gauche" si la valeur est inférieure à 350, sinon "Droite"
    if (valeurY < THRESHOLD_DOWN)
        return BAS;
    else if (valeurY > THRESHOLD_UP)
        return HAUT;
    return NEUTRE;
}

JoystickState Joystick::getStateX() {
    JoystickState jstate;
    jstate.direction = lireDirectionX();

    jstate.vientDeChanger = (jstate.direction != NEUTRE && jstate.direction != _lastDirectionX);
    _lastDirectionX = jstate.direction;

    return jstate;
}

JoystickState Joystick::getStateY() {
    JoystickState jstate;
    jstate.direction = lireDirectionY();

    jstate.vientDeChanger = (jstate.direction != NEUTRE && jstate.direction != _lastDirectionY);
    _lastDirectionY = jstate.direction;

    return jstate;
}
