#include "pausemenugui.h"
#include <QDebug>

PauseMenuGui::PauseMenuGui() {
    _cadre = new QGraphicsRectItem;
    _cadre->setRect(100, 100, 600, 400);
    _cadre->setBrush(Qt::white);

    _choix = new QGraphicsRectItem;

    short w = 0; // Taille des textes, pour les positionner exactement au milieu

    _textePause = new QGraphicsTextItem;
    _textePause->setPlainText("PAUSE");
    _textePause->setFont(QFont("Arial", 40));
    _textePause->setDefaultTextColor(Qt::black);
    w = _textePause->boundingRect().width();
    _textePause->setPos(400 - (w / 2.0), 150);

    _texteContinuer = new QGraphicsTextItem;
    _texteContinuer->setPlainText("Continuer");
    _texteContinuer->setFont(QFont("Arial", 20));
    _texteContinuer->setDefaultTextColor(Qt::black);
    w = _texteContinuer->boundingRect().width();
    _texteContinuer->setPos(400 - (w / 2.0), 325);

    _texteRetourMenu = new QGraphicsTextItem;
    _texteRetourMenu->setPlainText("Retour au menu");
    _texteRetourMenu->setFont(QFont("Arial", 20));
    _texteRetourMenu->setDefaultTextColor(Qt::black);
    w = _texteRetourMenu->boundingRect().width();
    _texteRetourMenu->setPos(400 - (w / 2.0), 400);

    _cadre->setZValue(100);
    _choix->setZValue(101);
    _textePause->setZValue(102);
    _texteContinuer->setZValue(103);
    _texteRetourMenu->setZValue(104);
}

void PauseMenuGui::sceneAjouter(QGraphicsScene* scene) {
    scene->addItem(_cadre);
    scene->addItem(_choix);
    scene->addItem(_textePause);
    scene->addItem(_texteContinuer);
    scene->addItem(_texteRetourMenu);
}

void PauseMenuGui::setVisible(bool visible) {
    _cadre->setVisible(visible);
    _choix->setVisible(visible);
    _textePause->setVisible(visible);
    _texteContinuer->setVisible(visible);
    _texteRetourMenu->setVisible(visible);
}

void PauseMenuGui::setChoixOption(int choix) {
    QGraphicsTextItem* texte;
    switch (choix) {
        case 0: texte = _texteContinuer;                                    break;
        case 1: texte = _texteRetourMenu;                                   break;
        default: qDebug() << "Choix d'option dans le menu pause invalide!"; return;
    }

    int x = texte->x() - PADDING_RECT_CHOIX;
    int y = texte->y() - PADDING_RECT_CHOIX;
    int w = texte->boundingRect().width() + (PADDING_RECT_CHOIX * 2);
    int h = texte->boundingRect().height() + (PADDING_RECT_CHOIX * 2);
    
    _choix->setRect(x, y, w, h);
}
