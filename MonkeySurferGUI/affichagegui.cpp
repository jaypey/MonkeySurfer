#include "affichagegui.h"
#include <QDebug>

AffichageGUI::AffichageGUI(Jeu* j, Menu* m) : Affichage(j, m) {
    // Scene du jeu
    _scene = new QGraphicsScene;
    _scene->setSceneRect(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y);

    // View du jeu
    setScene(_scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);

    // Sprite du joueur
    _singe = new QGraphicsRectItem;
    _singe->setRect(350, 400, 100, 100);
    _scene->addItem(_singe);

    // Sprites des lianes
    for (int i = 0; i < 5; i++) {
        int posXLiane = ((WINDOW_SIZE_X / 2) - 10) + (ESPACEMENT_LIANES * (i - 2));

        _lianes[i] = new QGraphicsRectItem;
        _lianes[i]->setRect(posXLiane, 0, 20, WINDOW_SIZE_Y);
        _scene->addItem(_lianes[i]);
    }

    // Timer qui update automatiquement le jeu ainsi que les graphiques Qt
    _updateTimer = new QTimer;
    QObject::connect(_updateTimer, SIGNAL(timeout()), this, SLOT(update()));
    _updateTimer->start(1000 / FPS);
}

void AffichageGUI::afficherJeu() {

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
    int x = _lianes[_jeu->getPositionJoueur().x]->rect().x() - 40;
    _singe->setRect(x, 400, 100, 100);
}
