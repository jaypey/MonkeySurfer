#include "joystick.h"

Joystick::Joystick() 
{
    _pinX = PIN_JOYSTICK_X;
    _pinY = PIN_JOYSTICK_Y;
    _lastDirectionX = NEUTRE;
    _lastDirectionY = NEUTRE;
    _lastRepeatX = 0;
    _lastRepeatY = 0;
    _isInitialRepeatX = false;
    _isInitialRepeatY = false;
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
        return HAUT;
    else if (valeurY > THRESHOLD_UP)
        return BAS;
    return NEUTRE;
}

JoystickState Joystick::getStateX() {
    JoystickState jstate;
    jstate.direction = lireDirectionX();

    bool newDir = (jstate.direction != _lastDirectionX);
    uint16_t delayJoystick = REPEAT_DELAY_JOYSTICK;

    // Determine si on utilise le delai de temps initial pour les repetitions
    if (newDir)
       _isInitialRepeatX = true;

    if (_isInitialRepeatX)
        delayJoystick = INITIAL_REPEAT_DELAY_JOYSTICK;

    // Verifie si on repete l'input du joystick s'il est maintenu a la meme place pendant un certain delai
    if (
        jstate.direction != NEUTRE
        && (newDir || millis() > _lastRepeatX + delayJoystick)
    ) {
        jstate.repetition = true;
        _lastRepeatX = millis();
        _isInitialRepeatX = newDir;
    }
    else
        jstate.repetition = false;

    // Direction du joystick
    _lastDirectionX = jstate.direction;

    return jstate;
}

JoystickState Joystick::getStateY() {
    JoystickState jstate;
    jstate.direction = lireDirectionY();

    bool newDir = (jstate.direction != _lastDirectionY);
    uint16_t delayJoystick = REPEAT_DELAY_JOYSTICK;

        // Determine si on utilise le delai de temps initial pour les repetitions
    if (newDir)
       _isInitialRepeatY = true;

    if (_isInitialRepeatY)
        delayJoystick = INITIAL_REPEAT_DELAY_JOYSTICK;

    // Verifie si on repete l'input du joystick s'il est maintenu a la meme place pendant un certain delai
    if  (
        jstate.direction != NEUTRE
        && (newDir || millis() > _lastRepeatY + delayJoystick)
    ) {
        jstate.repetition = true;
        _lastRepeatY = millis();
        _isInitialRepeatY = newDir;
    }
    else
        jstate.repetition = false;

    // Direction du joystick
    _lastDirectionY = jstate.direction;

    return jstate;
}
