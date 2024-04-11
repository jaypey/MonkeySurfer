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
#include "animatedpixmap.h"
#include "dustpuff.h"
#include "itemgui.h"
#include "pausemenugui.h"
#include "GameOverMenuGui.h"

#define WINDOW_SIZE_X 1920
#define WINDOW_SIZE_Y 1080
#define COORD_MAX_Y 21

#define NB_LIANES 5
#define ESPACEMENT_LIANES 200
#define LARGEUR_LIANES 20
#define HAUTEUR_LIANES 300

#define PADDING_ITEM1_JOUEUR 48.0
#define PADDING_ITEM2_JOUEUR 48.0

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
    Jeu* getjeu();
public slots:
    void update();
    void mouvementSinge();
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
    AnimatedPixmap* _singe;
    QGraphicsPixmapItem* _lianes[NB_LIANES * 3];
    QGraphicsPixmapItem* _background;
    QGraphicsPixmapItem* _backgroundLoop1;
    QGraphicsPixmapItem* _backgroundLoop2;
    PauseMenuGui* _menuPause;
    GameOverMenuGui* _menuGameover;

    QGraphicsTextItem* _score;
    QGraphicsTextItem* _piece;
    QGraphicsTextItem* _item;

    QGraphicsPixmapItem* _flecheGauche;
    QGraphicsPixmapItem* _flecheDroite;

    QGraphicsPixmapItem* _item1;
    QGraphicsPixmapItem* _item2;
    QGraphicsPixmapItem* _itemCadre1;
    QGraphicsPixmapItem* _itemCadre2;

    QGraphicsPixmapItem* _bouclierJoueur;
    QGraphicsPixmapItem* _serpentAutourJoueur;
    QGraphicsPixmapItem* _effetBanane;

    std::vector<ItemGui> _itemsGui;

    std::vector<DustPuff> _dustPuffs;
    std::chrono::steady_clock::time_point _lastDustPuffSpawn;

    QMediaPlayer* _mediaPlayer;
    QAudioOutput* _audioOutput;

    QTimer* _updateTimer;

    RandomGenerator _randGen;
};

#endif // !AFFICHAGEGUI_H
