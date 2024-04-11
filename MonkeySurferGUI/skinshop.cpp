#include "skinshop.h"
#include "jeu.h"

#include <QGraphicsGridLayout>

SkinShop::SkinShop()
{
	setupUI();
	loadSkins();
	displaySkins();
}
SkinShop::~SkinShop() {}



void SkinShop::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);

    //Vue 
    scene->setSceneRect(0, 0, 1920, 1080);
    view->setFixedSize(1920, 1080);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFrameStyle(QFrame::NoFrame);
    view->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->showFullScreen();

    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(view);
    this->setLayout(mainLayout);
    this->setFixedSize(1920, 1080);

    //Fond de jungle
    background = new QGraphicsPixmapItem;
    background->setPixmap(QPixmap(":\\sprites\\Background\\Background\\Background.png"));
    background->setPos(0, (-background->boundingRect().height() + 1080));
    scene->addItem(background);

    //Titre
    QFont junglefever(":/font/junglefever.ttf");
    titre = new QGraphicsTextItem;
    titre->setPlainText("MAGASIN");
    w = titre->boundingRect().width();
    titre->setDefaultTextColor(Qt::white);
    titre->setFont(QFont("junglefever", 100));
    titre->setPos(1920/2 - ((titre->boundingRect().width())/2) , 0);
    scene->addItem(titre);

    //pieces du joueur
    pieces = new QGraphicsTextItem;
    pieces->setPlainText("Vos pieces:");
    titre->setFont(QFont("junglefever", 35));
    pieces->setDefaultTextColor(Qt::black);
    pieces->setPos(45, 45);
    scene->addItem(pieces);

    //Bouton retour au menu
    exitButton = new QPushButton("Retour");
    connect(exitButton, &QPushButton::clicked, this, [this]() {
        this->setVisible(false);
        });

    buttonContainer = new QWidget;
    buttonLayout = new QHBoxLayout(buttonContainer);
    buttonLayout->addWidget(exitButton);
    buttonContainer->setLayout(buttonLayout);

    QGraphicsProxyWidget* proxyWidget = scene->addWidget(buttonContainer);
    // Adjust the button container to be at the bottom center
    proxyWidget->setPos(30, 1000);

}

void SkinShop::loadSkins() {

    for (int i = 1; i <= 9; ++i) {
        QString skinImagePath = QString(":/sprites/Skins/SkinShop/skin%1.png").arg(i);
        QGraphicsPixmapItem* skinItem = new QGraphicsPixmapItem(QPixmap(skinImagePath));
        skinItems.append(skinItem);
    }
}

void SkinShop::displaySkins() {
    int startXPos = 330;
    int startYPos = 180;
    int xPos = startXPos;
    int yPos = startYPos;
    int column = 0;

    for (auto& item : skinItems) {
        item->setPos(xPos, yPos);
        scene->addItem(item);

        xPos += 530; // Horizontal spacing
        column++;

        if (column % 3 == 0) {
            xPos = startXPos;
            yPos += 280; // Move down after every third skin
        }
    }
}