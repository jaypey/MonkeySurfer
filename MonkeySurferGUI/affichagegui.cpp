#include "affichagegui.h"
#include <QDebug>


AffichageGUI::AffichageGUI(Jeu* j, Menu* m) : Affichage(j, m) {
    // Scene du jeu
    _scene = new QGraphicsScene;
    _scene->setSceneRect(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y);
    QGraphicsPixmapItem* pixmap = new QGraphicsPixmapItem;
    pixmap->setPixmap(QPixmap(":\\sprites\\Skins\\Monkey\\Monkey_Climb\\Monkey_Climb1.png"));
    _scene->addItem(pixmap);

    // View du jeu
    setScene(_scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);

    // Sprite du joueur
    _singe = new QGraphicsRectItem;
    _singe->setRect(0, 0, 100, 100);
    _singe->setTransformOriginPoint(_singe->boundingRect().center());
    _scene->addItem(_singe);

    // Sprites des lianes
    for (int i = 0; i < NB_LIANES; i++) {
        int x = ((WINDOW_SIZE_X / 2) - (LARGEUR_LIANES / 2)) + (ESPACEMENT_LIANES * (i - 2));

        _lianes[i] = new QGraphicsRectItem;
        _lianes[i]->setRect(0, 0, LARGEUR_LIANES, WINDOW_SIZE_Y);
        _lianes[i]->setTransformOriginPoint(_lianes[i]->boundingRect().center());
        _lianes[i]->setPos(x, 0);
        _scene->addItem(_lianes[i]);
    }

    // Timer qui update automatiquement le jeu ainsi que les graphiques Qt
    _updateTimer = new QTimer;
    QObject::connect(_updateTimer, SIGNAL(timeout()), this, SLOT(update()));
    _updateTimer->start(1000 / FPS); // Nb ms par frame
}

void AffichageGUI::afficherJeu() {
    afficherArrierePlan();
    afficherLianes();
    afficherJoueur();
    afficherItems();
    afficherIU();
    // afficherGameOver();
    // afficherPause();
}

void AffichageGUI::afficherMenu() {

}

void AffichageGUI::update() {
    updateJeu();
    updateGUI();
}

void AffichageGUI::afficherArrierePlan() {

}

void AffichageGUI::afficherLianes() {

}

void AffichageGUI::afficherJoueur() {
    Coordonnee coord = transposerCoord(_jeu->getPositionJoueur(), _singe);
    _singe->setPos(coord.x, coord.y);
}

void AffichageGUI::afficherItems() {

}

void AffichageGUI::afficherIU() {

}

void AffichageGUI::afficherGameOver() {

}

void AffichageGUI::afficherPause() {

}

void AffichageGUI::updateJeu() {
    _jeu->getJsonSerial()->sendJson();
    _jeu->getJsonSerial()->recvJson();

    _jeu->debuterPartie();
    qDebug() << _jeu->getPointageJoueur() << ", " << _jeu->getPositionJoueur().x;
}

void AffichageGUI::updateGUI() {
    // afficherMenu();
    afficherJeu();
}

Coordonnee AffichageGUI::transposerCoord(const Coordonnee& coord, QGraphicsItem* item) {
    int w = item->boundingRect().width();
    int h = item->boundingRect().height();
    int x = _lianes[coord.x]->x() - (w / 2) + (LARGEUR_LIANES / 2);
    int y = _jeu->getPositionJoueur().y * (WINDOW_SIZE_Y / COORD_MAX_Y) - (h / 2);
    return { x, y };
}
