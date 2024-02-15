#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "jeu.h"

class Affichage
{
public:
    Affichage(Jeu *);
    virtual ~Affichage();

    virtual void afficherJeu() = 0;
    virtual void afficherMenu() = 0;
protected:
    virtual void afficherArrierePlan() = 0;
    virtual void afficherLianes() = 0;
    virtual void afficherJoueur() = 0;
    virtual void afficherItems() = 0;
    virtual void afficherObstacles() = 0;
    virtual void afficherIU() = 0; // IU = Interface usager (Ex. nb de points, etc.)

    Jeu *_jeu;
};

#endif // !AFFICHAGE_H
