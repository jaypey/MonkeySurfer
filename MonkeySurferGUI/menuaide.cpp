#include "menuaide.h"

MenuAide::MenuAide()
{
	_scene = new QGraphicsScene(this);
	_view = new QGraphicsView(_scene, this);

    //Trouver le centre l'écran pour y mettre le cadre avec le bon format
    QScreen* primaryScreen = QGuiApplication::primaryScreen();
    QRect screenGeometry = primaryScreen->geometry();


    //Fond de jungle
    _background = new QGraphicsPixmapItem((QPixmap(":\\sprites\\Background\\Background\\Background.png")));
    _background->setPos(0, (-_background->boundingRect().height() + 1080));
    _scene->addItem(_background);

    //panneau
    _panel = new QGraphicsPixmapItem(QPixmap(":\\sprites\\Background\\Background\\aide_bg.png"));
    _panel->setPos((screenGeometry.width()/2)-(_panel->boundingRect().width()/2), screenGeometry.height() - _panel->boundingRect().width());
}

MenuAide::~MenuAide()
{
}
