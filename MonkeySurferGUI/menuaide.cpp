#include "menuaide.h"
#include "menu.h"

MenuAide::MenuAide(Menu* m)
{
    _m = m;
	_scene = new QGraphicsScene(this);
    _scene->setSceneRect(0, 0, 1920, 1080);
	_view = new QGraphicsView(_scene, this);
    _view->setFixedSize(1920, 1080);
    _view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _view->setFrameStyle(QFrame::NoFrame);
    _view->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->showFullScreen();

    short w = 0; // Taille des textes, pour les positionner exactement au milieu

    //Fond de jungle
    _background = new QGraphicsPixmapItem((QPixmap(":\\sprites\\Background\\Background\\Background.png")));
    _background->setPos(0, (-_background->boundingRect().height() + 1080));
    _scene->addItem(_background);

    //panneau
    QPixmap panneau(":\\sprites\\Background\\Background\\aide_bg.png");
    panneau = panneau.scaled(1920, 1080, Qt::KeepAspectRatio);
    _panel = new QGraphicsPixmapItem(panneau);
    _panel->setScale(0.9);
    _panel->setPos((1920-_panel->boundingRect().width())/2,35);
    _scene->addItem(_panel);
    
    //piece
    _pieceTxt = new QGraphicsTextItem;
    _pieceTxt->setPlainText("Permet d'acheter des skins");
    _pieceTxt->setFont(QFont("Jungle Fever NF", 20));
    _pieceTxt->setPos(675, 350);
    _scene->addItem(_pieceTxt);
    
    
    QPixmap piecePix(":\\sprites\\Objets\\Piece\\coin.png");
    piecePix = piecePix.scaled(60, 60);
    _piece = new QGraphicsPixmapItem(piecePix);
    _piece->setPos(600, 340);
    _scene->addItem(_piece);

    //ruche
    _rucheTxt = new QGraphicsTextItem;
    _rucheTxt->setTextWidth(500);
    _rucheTxt->setPlainText("Evitez les ruches pour continuer de monter!");
    _rucheTxt->setFont(QFont("Jungle Fever NF", 20));
    _rucheTxt->setPos(675, 420);
    _scene->addItem(_rucheTxt);

    QPixmap ruchePix(":\\sprites\\Objets\\Ruche\\ruche.png");
    ruchePix = ruchePix.scaled(60, 60);
    _ruche = new QGraphicsPixmapItem(ruchePix);
    _ruche->setPos(600, 410);
    _scene->addItem(_ruche);

    //harpie
    _harpieTxt = new QGraphicsTextItem;
    _harpieTxt->setTextWidth(550);
    _harpieTxt->setPlainText("Ne vous faites pas attraper par les harpies, elles sont feroces!");
    _harpieTxt->setFont(QFont("Jungle Fever NF", 20));
    _harpieTxt->setPos(675, 515);
    _scene->addItem(_harpieTxt);

    QPixmap harpiePix(":\\sprites\\Objets\\Harpie\\harpie.png");
    harpiePix = harpiePix.scaled(60, 60);
    _harpie = new QGraphicsPixmapItem(harpiePix);
    _harpie->setPos(600, 505);
    _scene->addItem(_harpie);

    //serpent
    _serpentTxt = new QGraphicsTextItem;
    _serpentTxt->setTextWidth(550);
    _serpentTxt->setPlainText("Si un serpent vous attrape, secouez la manette pour le frapper!");
    _serpentTxt->setFont(QFont("Jungle Fever NF", 20));
    _serpentTxt->setPos(675, 600);
    _scene->addItem(_serpentTxt);

    QPixmap serpentPix(":\\sprites\\Objets\\Serpent\\snake.png");
    serpentPix = serpentPix.scaled(60, 60);
    _serpent = new QGraphicsPixmapItem(serpentPix);
    _serpent->setPos(600, 590);
    _scene->addItem(_serpent);

    //bouclier
    _bouclierTxt = new QGraphicsTextItem;
    _bouclierTxt->setTextWidth(550);
    _bouclierTxt->setPlainText("Activer le bouclier pour vous proteger dans la jungle sauvage!");
    _bouclierTxt->setFont(QFont("Jungle Fever NF", 20));
    _bouclierTxt->setPos(675, 680);
    _scene->addItem(_bouclierTxt);

    QPixmap bouclierPix(":\\sprites\\Objets\\Bouclier\\bubble.png");
    bouclierPix = bouclierPix.scaled(60, 60);
    _serpent = new QGraphicsPixmapItem(bouclierPix);
    _serpent->setPos(600, 670);
    _scene->addItem(_serpent);

    //banane
    _bananeTxt = new QGraphicsTextItem;
    _bananeTxt->setTextWidth(550);
    _bananeTxt->setPlainText("Mangez une banane pour faire de plus grands sauts!");
    _bananeTxt->setFont(QFont("Jungle Fever NF", 20));
    _bananeTxt->setPos(675, 760);
    _scene->addItem(_bananeTxt);

    QPixmap bananePix(":\\sprites\\Objets\\Banane\\banana.png");
    bananePix = bananePix.scaled(60, 60);
    _banane = new QGraphicsPixmapItem(bananePix);
    _banane->setPos(600, 750);
    _scene->addItem(_banane);

    //texte pour quitter
    setupUI();

    _timer = new QTimer;
    connect(_timer, SIGNAL(timeout()), this, SLOT(update()));
}

MenuAide::~MenuAide()
{
}

void MenuAide::startTimer()
{
    _timer->start(1000/60);
}

void MenuAide::update()
{
    _m->update();
    if (_m->getEtat() == Menu::EtatMenu::PRINCIPAL) {
        emit retourVersMenu();
        hide();
        _timer->stop();
    }
}

void MenuAide::setupUI()
{
    //Bouton retour au menu
    _exitButton = new QPushButton("Retour");
    connect(_exitButton, &QPushButton::clicked, this, [this] {
        emit retourVersMenu();
        this->hide();
        });

    buttonContainer = new QWidget;
    buttonLayout = new QHBoxLayout(buttonContainer);
    buttonLayout->addWidget(_exitButton);
    buttonContainer->setLayout(buttonLayout);


    QGraphicsProxyWidget* proxyWidget = _scene->addWidget(buttonContainer);
    proxyWidget->setPos(30, 1000);

}
