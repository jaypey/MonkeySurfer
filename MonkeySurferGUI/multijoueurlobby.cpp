#include "multijoueurlobby.h"
#include "jeu.h"
#include "joueur.h"

#include <QGraphicsGridLayout>

MultijoueurLobby::MultijoueurLobby(Joueur* _j)
{
    joueur = _j;
    setupUI();
}
MultijoueurLobby::~MultijoueurLobby() {}

void MultijoueurLobby::updateConnectedPlayers(int playerCount) {
    m_playerCount = playerCount;
}


void MultijoueurLobby::setupUI() {
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

    titre = new QGraphicsTextItem;
    titre->setPlainText("MULTIJOUEUR");
    titre->setDefaultTextColor(Qt::white);
    titre->setFont(QFont("Jungle Fever NF", 100));
    titre->setPos(1920 / 2 - ((titre->boundingRect().width()) / 2), 0);
    scene->addItem(titre);

    //pieces du joueur


    pieces = new QGraphicsTextItem;
    pieces->setPlainText(QString("Joueurs connectés: "));
    pieces->setFont(QFont("Jungle Fever NF", 25));
    pieces->setDefaultTextColor(Qt::white);
    pieces->setPos(1920 - 50, 1080 - 50);
    scene->addItem(pieces);

    imgpiece = new QGraphicsPixmapItem;



    //Bouton retour au menu
    exitButton = new QPushButton("Retour");
    connect(exitButton, &QPushButton::clicked, this, [this] {
        this->hide();

        });

    buttonContainer = new QWidget;
    buttonLayout = new QHBoxLayout(buttonContainer);
    buttonLayout->addWidget(exitButton);
    buttonContainer->setLayout(buttonLayout);


    QGraphicsProxyWidget* proxyWidget = scene->addWidget(buttonContainer);
    proxyWidget->setPos(30, 1000);


}