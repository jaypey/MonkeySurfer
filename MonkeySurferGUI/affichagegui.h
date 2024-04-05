#ifndef AFFICHAGEGUI_H
#define AFFICHAGEGUI_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "affichage.h"

#define WINDOW_SIZE_X 800
#define WINDOW_SIZE_Y 600
#define ESPACEMENT_LIANES 100

class AffichageGUI : public Affichage, public QGraphicsView {
public:
    AffichageGUI(Jeu* j, Menu* m);

    void afficherJeu();
    void afficherMenu();
protected:
    void afficherArrierePlan();
    void afficherLianes();
    void afficherJoueur();
    void afficherItems();
    void afficherIU();
    void afficherGameOver();
    void afficherPause();
private:
    QGraphicsScene* _scene;
    QGraphicsRectItem* _singe;
    QGraphicsRectItem* _lianes[5];
};

#endif // !AFFICHAGEGUI_H
