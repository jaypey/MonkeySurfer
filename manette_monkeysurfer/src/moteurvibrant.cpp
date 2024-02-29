# include "moteurvibrant.h"

MoteurVibrant::MoteurVibrant()
{
    this->pinMoteur = PIN_MOTEUR_VIBRANT;
    // Configuration de la broche du moteur en sortie
    pinMode(pinMoteur, OUTPUT);
}

MoteurVibrant::MoteurVibrant(int p_pinMoteur) 
{
    this->pinMoteur = p_pinMoteur;
    
    // Configuration de la broche du moteur en sortie
    pinMode(pinMoteur, OUTPUT);
}

void MoteurVibrant::controlerMoteur(int etat) 
{
    digitalWrite(pinMoteur, etat);
}