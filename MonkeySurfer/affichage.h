#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "jeu.h"
#include "menu.h"

#ifdef USE_QT
#include <QGraphicsView>
#endif

class Affichage
#ifdef USE_QT
    : public QGraphicsView
#endif
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
    virtual void afficherPause() = 0;

    Jeu *_jeu;
    Menu *_menu;
};

#endif // !AFFICHAGE_H
