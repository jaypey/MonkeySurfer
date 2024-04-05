#include "affichagegui.h"

AffichageGUI::AffichageGUI(Jeu* j, Menu* m) : Affichage(j, m) {
    _scene = new QGraphicsScene;
    _scene->setSceneRect(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y);

    setScene(_scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);

    _singe = new QGraphicsRectItem;
    _singe->setRect(350, 400, 100, 100);
    _scene->addItem(_singe);

    for (int i = 0; i < 5; i++) {
        int posXLiane = ((WINDOW_SIZE_X / 2) - 10) - (ESPACEMENT_LIANES * (i - 2));

        _lianes[i] = new QGraphicsRectItem;
        _lianes[i]->setRect(posXLiane, 0, 20, WINDOW_SIZE_Y);
        _scene->addItem(_lianes[i]);
    }
}

void AffichageGUI::afficherJeu() {

}

void AffichageGUI::afficherMenu() {

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
