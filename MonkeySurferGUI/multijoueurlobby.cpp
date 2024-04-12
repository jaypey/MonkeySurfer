#include "multijoueurlobby.h"
#include "jeu.h"
#include "menu.h"

#include <QGraphicsGridLayout>

MultijoueurLobby::MultijoueurLobby(Menu* m, AffichageGUI* affi)
{
    _affichage = affi;
    _menu = m;
    setupUI();
    _timer = new QTimer;
    QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(updateNetwork()));
}
MultijoueurLobby::~MultijoueurLobby() {}

void MultijoueurLobby::startUpdateLoop()
{
    _timer->start(1000 / 60);
    _menu->updateMultijoueur();
}

void MultijoueurLobby::updateNetwork()
{
    if (_affichage->isHidden()) {
        if (_kbhit())
        {
             char c = _getch();
            if(c == 'r'){
                _menu->updateEtatReady();
                messagePretOui->setPlainText(QString("Vous etes pret"));
            }
        }
        if (_menu->getJsonSerial()->boutonAppuye(0)) {
            _menu->updateEtatReady();
            messagePretOui->setPlainText(QString("Vous etes pret"));
        }
        updateConnectedPlayers();
        if (_menu->getNetworking()->IsGameStarted())
        {
            _menu->setEtat(Menu::EtatMenu::MULTIJOUEURJEU);
            _affichage->reset();
            _affichage->getjeu()->getJoueur()->reset();
            _affichage->getjeu()->restartJeu(_affichage->getjeu()->getJoueur());
            _affichage->showFullScreen();
            hide();

        }
    }
}

void MultijoueurLobby::updateConnectedPlayers() {
    messagePret->setPlainText(QString("Veuillez appuyer sur 'R' lorsque vous etes pret! \n Joueurs : " + QString::number(_menu->getNbMultijoueurReady()) + "/" + QString::number(_menu->getNbMultijoueurConnectes())));
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

    messagePret = new QGraphicsTextItem;
    messagePret->setPlainText(QString("Veuillez appuyer sur 'R' lorsque vous etes pret! \n Joueurs : " + QString::number(_menu->getNbMultijoueurReady()) + "/" + QString::number(_menu->getNbMultijoueurConnectes())));
    messagePret->setFont(QFont("Jungle Fever NF", 25));
    messagePret->setDefaultTextColor(Qt::white);
    messagePret->setPos(1920/2 - messagePret->boundingRect().width(), 1080 / 2);
    scene->addItem(messagePret);

    messagePretOui = new QGraphicsTextItem;
    messagePretOui->setFont(QFont("Jungle Fever NF", 25));
    messagePretOui->setDefaultTextColor(Qt::white);
    messagePretOui->setPos(messagePret->pos().x(), messagePret->pos().y() - messagePret->boundingRect().height());
    scene->addItem(messagePretOui);




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