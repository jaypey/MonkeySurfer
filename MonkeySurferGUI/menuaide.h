#ifndef MENUAIDE_H
#define MENUAIDE_H

#include <QGuiApplication>
#include <QScreen>
#include <QGraphicsTextItem>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
class MenuAide : public QWidget
{
	Q_OBJECT

public:
	explicit MenuAide();
	~MenuAide();

private:
	QGraphicsScene* _scene;
	QGraphicsView* _view;

	QGraphicsPixmapItem* _background;
	QGraphicsPixmapItem* _panel;
	QGraphicsTextItem* _titre;
	QGraphicsPixmapItem* _singe;
	QGraphicsPixmapItem* _ruche;
	QGraphicsPixmapItem* _serpent;
	QGraphicsPixmapItem* _harpie;
	QGraphicsPixmapItem* _bouclier;
	QGraphicsPixmapItem* _banane;
	QGraphicsTextItem* _singeTxt;
	QGraphicsTextItem* _rucheTxt;
	QGraphicsTextItem* _serpentTxt;
	QGraphicsTextItem* _harpieTxt;
	QGraphicsTextItem* _bouclierTxt;
	QGraphicsTextItem* _bananeTxt;
};

#endif // !MENUAIDE_H



