#include "GameOverMenuGui.h"

GameOverMenuGui::GameOverMenuGui(Jeu* j)
{
    _j = j;

    QFont junglefever(":/font/junglefever.ttf");
    QFontDatabase::addApplicationFont(":/font/junglefever.ttf");

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

    short w = 0; // Taille des textes, pour les positionner exactement au milieu

    _gameOverTxt = new QGraphicsTextItem;
    _gameOverTxt->setPlainText("GAME OVER");
    _gameOverTxt->setDefaultTextColor(Qt::red);
    _gameOverTxt->setFont(QFont("junglefever", cadreRect.height() * 0.08));
    w = _gameOverTxt->boundingRect().width();
    _gameOverTxt->setPos((cadreX + (cadreRect.width() / 2)) - (w / 2), (cadreY + (cadreRect.height() * 0.25)));

    _score = new QGraphicsTextItem;
    _score->setPlainText(QString("Score : ") + QString::number(0));
    _score->setFont(QFont("junglefever", cadreRect.height() * 0.04));
    w = _score->boundingRect().width();
    _score->setPos((cadreX + (cadreRect.width() / 2)) - (w / 2), (cadreY + (cadreRect.height() * 0.4)));

    _pieces = new QGraphicsTextItem;
    _pieces->setPlainText(QString("Total des pièces : ") + QString::number(0));
    _pieces->setFont(QFont("junglefever", cadreRect.height() * 0.04));
    w = _pieces->boundingRect().width();
    _pieces->setPos((cadreX + (cadreRect.width() / 2)) - (w / 2), (cadreY + (cadreRect.height() * 0.5)));

    _menu = new QGraphicsTextItem;
    _menu->setPlainText("Menu");
    _menu->setFont(QFont("junglefever", cadreRect.height() * 0.04));
    _menu->setDefaultTextColor(QColor("#32a150"));
    _menu->setPos(cadreX + (cadreRect.width() / 2) - 175, cadreY + cadreRect.height() - 250);

    _rejouer = new QGraphicsTextItem;
    _rejouer->setPlainText("Rejouer");
    _rejouer->setFont(QFont("junglefever", cadreRect.height() * 0.04));
    _rejouer->setDefaultTextColor(QColor("#32a150"));
    _rejouer->setPos(cadreX + (cadreRect.width() / 2) + 25, cadreY + cadreRect.height() - 250);

    _choix = new QGraphicsRectItem;
    _choix->setBrush(QColor("#32a150"));
    _choix->setPen(QPen(Qt::transparent));

    _cadre->setZValue(200);
    _choix->setZValue(206);
    _pieces->setZValue(202);
    _score->setZValue(203);
    _gameOverTxt->setZValue(204);
    _menu->setZValue(205);
    _rejouer->setZValue(206);

}

void GameOverMenuGui::sceneAjouter(QGraphicsScene* scene)
{
    // Add cadre and text items
    scene->addItem(_cadre);
    scene->addItem(_gameOverTxt);
    scene->addItem(_score);
    scene->addItem(_pieces);
    scene->addItem(_choix);
    scene->addItem(_menu);
    scene->addItem(_rejouer);
}

void GameOverMenuGui::setVisible(bool visible)
{
    _score->setVisible(visible);
    _pieces->setVisible(visible);
    _cadre->setVisible(visible);
    _gameOverTxt->setVisible(visible);
    _choix->setVisible(visible);
    _menu->setVisible(visible);
    _rejouer->setVisible(visible);
}

void GameOverMenuGui::setChoixOption(int choix) {
    if (choix == 0) {
        _choix->setRect(_menu->x(), _menu->y() + _menu->boundingRect().height(), _menu->boundingRect().width(), 5);
    }
    else if (choix == 1) {
        _choix->setRect(_rejouer->x(), _rejouer->y() + _rejouer->boundingRect().height(), _rejouer->boundingRect().width(), 5);
    }
}

void GameOverMenuGui::setScore()
{
    _score->setPlainText(QString("Score : ") + QString::number(_j->getPointageJoueur()));
}

void GameOverMenuGui::setPiece()
{
    _pieces->setPlainText(QString::fromUtf8("Total des pieces : ") + QString::number(_j->getPiecesJoueur()));
}
