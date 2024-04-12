#include "skinshop.h"
#include "jeu.h"
#include "joueur.h"
#include "menu.h"

#include <QGraphicsGridLayout>

SkinShop::SkinShop(Joueur* _j, Skin* skins, Menu* menu) 
{
    this->skins = skins;
    joueur = _j;
    _m = menu;
	setupUI();
	skinItems.resize(9);
    _details.resize(9);
    displaySkins();
    update_timer = new QTimer;
    QObject::connect(update_timer, SIGNAL(timeout()), this, SLOT(update()));
}
SkinShop::~SkinShop() {}

void SkinShop::startTimer()
{
    update_timer->start(1000 / 60);
}

void SkinShop::quitter()
{
    update_timer->stop();
}

void SkinShop::update()
{
    _m->update();

    int indexSelect = _m->getIndexSkinPreview();
    int X_cadre = skinItems[indexSelect]->x() - 92;
    int Y_cadre = skinItems[indexSelect]->y() - 92;
    _cadre->setPos(X_cadre,Y_cadre);

    int indexEquipped = _m->getIndexSkin();
    int X_glow = skinItems[indexEquipped]->x() - 100;
    int Y_glow = skinItems[indexEquipped]->y() - 100;
    _glow->setPos(X_glow, Y_glow);
    _glow->setRotation(_glow->rotation() + 1);

    pieces->setPlainText(QString("Vos pieces: ") + QString::number(joueur->getPiece()));

    for (int i = 0; i < 9; ++i) {
        // Display the skins
        const Skin& skin = skins[i];
        QString details = QString::fromStdString(skin.getId() + std::string(" $") + std::to_string(skin.getPrix()));
        if (skin.isDebloque()) {
            details += "\n(OBTENU)";
            _details[i]->setPlainText(details);
        }
    }
    
}

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
    titre = new QGraphicsTextItem;
    titre->setPlainText("MAGASIN");
    w = titre->boundingRect().width();
    titre->setDefaultTextColor(Qt::white);
    titre->setFont(QFont("Jungle Fever NF", 100));
    titre->setPos(1920/2 - ((titre->boundingRect().width())/2) , 0);
    scene->addItem(titre);

    //Glow
    _glow = new QGraphicsPixmapItem;
    _glow->setPixmap(QPixmap(":\\sprites\\Objets\\Banane\\effetBanana.png"));
    _glow->setTransformOriginPoint(_glow->boundingRect().width() / 2, _glow->boundingRect().height() / 2);
    _glow->setScale(0.7);
    _glow->setOpacity(0.7);
    scene->addItem(_glow);

    //cadre de selection
    _cadre = new QGraphicsPixmapItem;
    _cadre->setPixmap(QPixmap(":\\sprites\\UI\\cadre_vine_gros.png"));
    _cadre->setPos((330-92), (180-92));
    scene->addItem(_cadre);

    //pieces du joueur
    pieces = new QGraphicsTextItem;
    pieces->setPlainText(QString("Vos pieces: ") + QString::number(joueur->getPiece()));
    pieces->setFont(QFont("junglefever", 25));
    pieces->setDefaultTextColor(Qt::white);
    pieces->setPos(45, 45);
    scene->addItem(pieces);
    //img de la piece
    imgpiece = new QGraphicsPixmapItem;
    imgpiece->setPixmap(QPixmap(":/sprites/Objets/Piece/coin.png"));
    imgpiece->setPos((80 + pieces->boundingRect().width()), 40);
    scene->addItem(imgpiece);
    


    //Bouton retour au menu
    exitButton = new QPushButton("Retour");
    connect(exitButton, &QPushButton::clicked, this, [this]  {
        emit retourMenu();
        this->hide();
        });

    buttonContainer = new QWidget;
    buttonLayout = new QHBoxLayout(buttonContainer);
    buttonLayout->addWidget(exitButton);
    buttonContainer->setLayout(buttonLayout);
    

    QGraphicsProxyWidget* proxyWidget = scene->addWidget(buttonContainer);
    proxyWidget->setPos(30, 1000);
    

}



void SkinShop::displaySkins() {
   
    int startXPos = 330;
    int startYPos = 180;
    int xPos = startXPos;
    int yPos = startYPos;
    int column = 0;

    for (int i = 0; i < 9; ++i) {
        // Display the skins
        const Skin& skin = skins[i];
        skinItems[i] = new QGraphicsPixmapItem(QPixmap(skin.getFile()));
        skinItems[i]->setPos(xPos, yPos);
        scene->addItem(skinItems[i]);

        // Display skin name and price or ownership status
        QString details = QString::fromStdString(skin.getId() + std::string(" $") + std::to_string(skin.getPrix()));
        if (skin.isDebloque()) {
            details += "\n(OBTENU)";
        }
        _details[i] = new QGraphicsTextItem(details);
        _details[i]->setDefaultTextColor(Qt::white);
        QFont font = _details[i]->font();
        font.setPointSize(20);  
        _details[i]->setFont(font);

        // Calculate width of the text and adjust position to center it under the image
        QRectF textRect = _details[i]->boundingRect();
        qreal textStartPos = xPos + (200 - textRect.width()) / 2;  
        _details[i]->setPos(textStartPos, yPos + 200);
        scene->addItem(_details[i]);

        xPos += 500;  
        column++;

        if (column % 3 == 0) {
            xPos = startXPos;
            yPos += 280;  
        }
    } 
}