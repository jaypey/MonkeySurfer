#include "pausemenugui.h"
#include <QDebug>

PauseMenuGui::PauseMenuGui() {
    QPixmap cadrePixMap(":/sprites/Background/GameOver/cadre_bambou.png");
    if (cadrePixMap.isNull()) {
        qDebug() << "Failed to load game over image!";
        return;
    }

    //Trouver le centre l'écran pour y mettre le cadre avec le bon format
    QScreen* primaryScreen = QGuiApplication::primaryScreen();
    QRect screenGeometry = primaryScreen->geometry();
    cadrePixMap = cadrePixMap.scaled(screenGeometry.width() * 0.7, screenGeometry.height() * 0.7, Qt::KeepAspectRatio);

    _cadre = new QGraphicsPixmapItem(cadrePixMap);

    QRectF cadreRect = _cadre->boundingRect();
    qreal cadreX = (screenGeometry.width() - cadreRect.width()) / 2;
    qreal cadreY = (screenGeometry.height() - cadreRect.height()) / 2;
    _cadre->setPos(cadreX, cadreY);

    _choix = new QGraphicsRectItem;
    _choix->setBrush(QColor("#32a150"));
    _choix->setPen(QPen(Qt::transparent));

    short w = 0; // Taille des textes, pour les positionner exactement au milieu

    _textePause = new QGraphicsTextItem;
    _textePause->setPlainText("PAUSE");
    _textePause->setFont(QFont("Jungle Fever NF", cadreRect.height() * 0.08));
    _textePause->setDefaultTextColor(Qt::white);
    w = _textePause->boundingRect().width();
    _textePause->setPos((cadreX + (cadreRect.width() / 2)) - (w / 2), (cadreY + (cadreRect.height() * 0.25)));

    _texteContinuer = new QGraphicsTextItem;
    _texteContinuer->setPlainText("Continuer");
    _texteContinuer->setFont(QFont("Jungle Fever NF", cadreRect.height() * 0.04));
    _texteContinuer->setDefaultTextColor(QColor("#32a150"));
    w = _texteContinuer->boundingRect().width();
    _texteContinuer->setPos((cadreX + (cadreRect.width() / 2)) - (w / 2), (cadreY + (cadreRect.height() * 0.5)));

    _texteRetourMenu = new QGraphicsTextItem;
    _texteRetourMenu->setPlainText("Retour au menu");
    _texteRetourMenu->setFont(QFont("Jungle Fever NF", cadreRect.height() * 0.04));
    _texteRetourMenu->setDefaultTextColor(QColor("#32a150"));
    w = _texteRetourMenu->boundingRect().width();
    _texteRetourMenu->setPos((cadreX + (cadreRect.width() / 2)) - (w / 2), (cadreY + (cadreRect.height() * 0.6)));

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

    _choix->setRect(texte->pos().x()- PADDING_RECT_CHOIX, texte->pos().y() + texte->boundingRect().height()+PADDING_RECT_CHOIX,
        texte->boundingRect().width() + (2*PADDING_RECT_CHOIX), 6);
}
