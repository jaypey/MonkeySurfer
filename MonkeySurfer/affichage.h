#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "jeu.h"

class Affichage
{
public:
    Affichage(Jeu *);
    virtual ~Affichage();

    virtual void afficher() = 0;
    virtual void afficherArrierePlan() = 0;
    virtual void afficherLianes() = 0;
    virtual void afficherJoueur() = 0;
    virtual void afficherItems() = 0;
    virtual void afficherObstacles() = 0;
    virtual void afficherIU() = 0; // IU = Interface usager (Ex. nb de points, etc.)
protected:
    Jeu *_jeu;
};

#endif // !AFFICHAGE_H
