#include "GameOverMenuGui.h"

GameOverMenuGui::GameOverMenuGui(Jeu* j)
{
    _j = j;
    _widgetBtns = new QWidget;
    _layout = new QGridLayout(_widgetBtns);
    _widgetBtns->setLayout(_layout);

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


    _choix = new QGraphicsRectItem;

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

    _retourMenuBtn = new QPushButton("Menu");
    connect(_retourMenuBtn, &QPushButton::released, this, &GameOverMenuGui::btnMenu);
    _layout->addWidget(_retourMenuBtn);

    _rejouerBtn = new QPushButton("Rejouer");
    connect(_rejouerBtn, &QPushButton::released, this, &GameOverMenuGui::btnRejouer);
    _layout->addWidget(_rejouerBtn);

    _cadre->setZValue(200);
    _pieces->setZValue(202);
    _score->setZValue(203);
    _gameOverTxt->setZValue(204);

}

void GameOverMenuGui::sceneAjouter(QGraphicsScene* scene)
{
    // Add cadre and text items
    scene->addItem(_cadre);
    scene->addItem(_gameOverTxt);
    scene->addItem(_score);
    scene->addItem(_pieces);

    // Set background color of widgetBtns to be transparent
    _widgetBtns->setStyleSheet("background-color: transparent; color: #32a150");

    // Calculate the position to center the layout on the screen
    qreal screenWidth = scene->sceneRect().width();
    qreal screenHeight = scene->sceneRect().height();
    qreal layoutWidth = _widgetBtns->width();
    qreal layoutHeight = _widgetBtns->height();
    qreal layoutX = (screenWidth - layoutWidth) / 2;
    qreal layoutY = (screenHeight - layoutHeight) / 2;
 
    // Increase spacing between buttons in the layout
    _layout->setSpacing(100);// Adjust spacing as needed
    // Add container widget to scene and set its position
    QGraphicsProxyWidget* proxyWidget = scene->addWidget(_widgetBtns);
    proxyWidget->setPos(_cadre->pos().x()+(_cadre->boundingRect().width()/2)-(_layout->geometry().width() / 2)-50, 
        _cadre->pos().y()+(_cadre->boundingRect().height()*0.65));
    proxyWidget->setZValue(205); // Ensure it's displayed on top of _cadre

    // Set font size for buttons
    QFont buttonFont("junglefever", _cadre->sceneBoundingRect().height() * 0.04); // Adjust font size as needed
    for (QPushButton* button : _widgetBtns->findChildren<QPushButton*>()) {
        button->setFont(buttonFont);
    }
}

void GameOverMenuGui::setVisible(bool visible)
{
    _score->setVisible(visible);
    _pieces->setVisible(visible);
    _cadre->setVisible(visible);
    _gameOverTxt->setVisible(visible);
    
    
    for (QWidget* widget : _widgetBtns->findChildren<QPushButton*>()) {
        widget->setVisible(visible);
    }
    
}

void GameOverMenuGui::setChoixOption(int choix)
{
}

void GameOverMenuGui::setScore()
{
    _score->setPlainText(QString("Score : ") + QString::number(_j->getPointageJoueur()));
}

void GameOverMenuGui::setPiece()
{
    _pieces->setPlainText(QString::fromUtf8("Total des pièces : ") + QString::number(_j->getPiecesJoueur()));
}

void GameOverMenuGui::btnMenu()
{
    qDebug() << "Menu";
}

void GameOverMenuGui::btnRejouer()
{
    qDebug() << "Rejouer";
}