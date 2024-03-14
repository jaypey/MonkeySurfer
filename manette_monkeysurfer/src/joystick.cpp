#include "joystick.h"

Joystick::Joystick() 
{
    this->pinX = PIN_JOYSTICK_X;
    this->pinY = PIN_JOYSTICK_Y;
}

Joystick::Joystick(uint8_t p_pinX, uint8_t p_pinY) 
{
    this->pinX = p_pinX;
    this->pinY = p_pinY;
}

Direction Joystick::lireDirectionX()
{
    // Lecture de la valeur de l'axe X du joystick
    int valeurX = analogRead(pinX);

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
    int valeurY = analogRead(pinY);
    
    // Retourner "Gauche" si la valeur est inférieure à 350, sinon "Droite"
    if (valeurY < THRESHOLD_DOWN)
        return BAS;
    else if (valeurY > THRESHOLD_UP)
        return HAUT;
    return NEUTRE;
}
