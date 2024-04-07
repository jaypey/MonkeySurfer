#ifndef AFFICHAGEGUI_H
#define AFFICHAGEGUI_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include "affichage.h"
#include "pausemenugui.h"

#define WINDOW_SIZE_X 800
#define WINDOW_SIZE_Y 600
#define COORD_MAX_Y 21

#define NB_LIANES 5
#define ESPACEMENT_LIANES 100
#define LARGEUR_LIANES 20

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

    // Transpose les position du jeu de base a l'interface GUI
    Coordonnee transposerCoord(const Coordonnee& coord, QGraphicsItem* item);

    QGraphicsScene* _scene;
    QGraphicsRectItem* _singe;
    QGraphicsRectItem* _lianes[NB_LIANES];
    PauseMenuGui* _menuPause;

    QTimer* _updateTimer;
};

#endif // !AFFICHAGEGUI_H
