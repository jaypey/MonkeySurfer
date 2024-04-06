#ifndef AFFICHAGEGUI_H
#define AFFICHAGEGUI_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include "affichage.h"

#define WINDOW_SIZE_X 800
#define WINDOW_SIZE_Y 600
#define ESPACEMENT_LIANES 100

#define FPS 30

class AffichageGUI : public Affichage {
    Q_OBJECT
public:
    AffichageGUI(Jeu* j, Menu* m);

    void afficherJeu();
    void afficherMenu();
public slots:
    void update();
private:
    void afficherArrierePlan();
    void afficherLianes();
    void afficherJoueur();
    void afficherItems();
    void afficherIU();
    void afficherGameOver();
    void afficherPause();

    void updateJeu();
    void updateGUI();

    QGraphicsScene* _scene;
    QGraphicsRectItem* _singe;
    QGraphicsRectItem* _lianes[5];
    QTimer* _updateTimer;
};

#endif // !AFFICHAGEGUI_H
