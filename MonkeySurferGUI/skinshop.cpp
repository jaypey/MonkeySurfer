#include "skinshop.h"
#include "jeu.h"
#include "joueur.h"

#include <QGraphicsGridLayout>

SkinShop::SkinShop(Joueur* _j, Skin* skins) 
{
    this->skins = skins;
    joueur = _j;
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
    
    titre = new QGraphicsTextItem;
    titre->setPlainText("MAGASIN");
    w = titre->boundingRect().width();
    titre->setDefaultTextColor(Qt::white);
    titre->setFont(QFont("Jungle Fever NF", 100));
    titre->setPos(1920/2 - ((titre->boundingRect().width())/2) , 0);
    scene->addItem(titre);

    //pieces du joueur
    

    pieces = new QGraphicsTextItem;
    pieces->setPlainText(QString("Vos pieces: ") + QString::number(joueur->getPiece()));
    pieces->setFont(QFont("junglefever", 25));
    pieces->setDefaultTextColor(Qt::white);
    pieces->setPos(45, 45);
    scene->addItem(pieces);

    imgpiece = new QGraphicsPixmapItem;
    imgpiece->setPixmap(QPixmap(":/sprites/Objets/Piece/coin.png"));
    imgpiece->setPos((80 + pieces->boundingRect().width()), 40);
    scene->addItem(imgpiece);
    


    //Bouton retour au menu
    exitButton = new QPushButton("Retour");
    connect(exitButton, &QPushButton::clicked, this, [this]  {
        this->hide();

        });

    buttonContainer = new QWidget;
    buttonLayout = new QHBoxLayout(buttonContainer);
    buttonLayout->addWidget(exitButton);
    buttonContainer->setLayout(buttonLayout);
    

    QGraphicsProxyWidget* proxyWidget = scene->addWidget(buttonContainer);
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

    for (int i = 0; i < 9; ++i) {
        // Display the skins
        const Skin& skin = skins[i];
        auto* skinItem = new QGraphicsPixmapItem(QPixmap(skin.getFile()));
        skinItem->setPos(xPos, yPos); 
        skinItem->setScale(200.0 / skinItem->boundingRect().width()); 
        scene->addItem(skinItem);

        // Display skin name and price or ownership status
        QString details = QString::fromStdString(skin.getId() + std::string(" $") + std::to_string(skin.getPrix()));
        if (skin.isDebloque()) {
            details += "\n(OBTENU)";
        }
        auto* detailsItem = new QGraphicsTextItem(details);
        detailsItem->setDefaultTextColor(Qt::white);
        QFont font = detailsItem->font();
        font.setPointSize(20);  
        detailsItem->setFont(font);

        // Calculate width of the text and adjust position to center it under the image
        QRectF textRect = detailsItem->boundingRect();
        qreal textStartPos = xPos + (200 - textRect.width()) / 2;  
        detailsItem->setPos(textStartPos, yPos + 200);  
        scene->addItem(detailsItem);

        xPos += 500;  
        column++;

        if (column % 3 == 0) {
            xPos = startXPos;
            yPos += 280;  
        }
    }
   
  
}