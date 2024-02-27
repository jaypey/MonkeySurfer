#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "jeu.h"
#include "menu.h"

class Affichage
{
public:
    Affichage(Jeu *j, Menu *m);
    virtual ~Affichage();

    virtual void afficherJeu() = 0;
    virtual void afficherMenu() = 0;
protected:
    virtual void afficherArrierePlan() = 0;
    virtual void afficherLianes() = 0;
    virtual void afficherJoueur() = 0;
    virtual void afficherItems() = 0;
    virtual void afficherIU() = 0; // IU = Interface usager (Ex. nb de points, etc.)
    virtual void afficherGameOver() = 0;

    Jeu *_jeu;
    Menu *_menu;
};

#endif // !AFFICHAGE_H
