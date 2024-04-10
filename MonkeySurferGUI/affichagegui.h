#ifndef AFFICHAGEGUI_H
#define AFFICHAGEGUI_H

#include <chrono>
#include <cmath>
#include <vector>
#include <QAudioOutput>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QTimer>
#include "affichage.h"
#include "aleatoire.h"
#include "dustpuff.h"
#include "itemgui.h"
#include "pausemenugui.h"

#define WINDOW_SIZE_X 1920
#define WINDOW_SIZE_Y 1080
#define COORD_MAX_Y 21

#define NB_LIANES 5
#define ESPACEMENT_LIANES 200
#define LARGEUR_LIANES 20

#define PADDING_ITEM_JOUEUR 10.0

#define DIST_SPAWN_DUSTPUFF 40.0
#define PEAK_SCALE_DUSTPUFF 0.7
#define LIFESPAN_DUSTPUFF 1000.0 // En ms
#define SPAWN_DELAY_DUSTPUFF 200 // En ms

#define FPS 60

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
    void updateItemGUI();

    void createDustPuff();
    void updateDustPuff(int vecIndex);
    bool canSpawnDustPuff();

    // Transpose les position du jeu de base a l'interface GUI
    Coordonnee transposerCoord(const Coordonnee& coord, QGraphicsItem* item);

    QGraphicsScene* _scene;
    QGraphicsPixmapItem* _singe;
    QGraphicsPixmapItem* _lianes[NB_LIANES];
    QGraphicsPixmapItem* _background;
    PauseMenuGui* _menuPause;

    QGraphicsTextItem* _score;
    QGraphicsTextItem* _piece;
    QGraphicsTextItem* _item;

    QGraphicsPixmapItem* _flecheGauche;
    QGraphicsPixmapItem* _flecheDroite;

    QGraphicsRectItem* _item1;
    QGraphicsRectItem* _item2;
    QGraphicsRectItem* _itemCadre1;
    QGraphicsRectItem* _itemCadre2;

    std::vector<ItemGui> _itemsGui;

    std::vector<DustPuff> _dustPuffs;
    std::chrono::steady_clock::time_point _lastDustPuffSpawn;

    QMediaPlayer* _mediaPlayer;
    QAudioOutput* _audioOutput;

    QTimer* _updateTimer;

    RandomGenerator _randGen;
};

#endif // !AFFICHAGEGUI_H
