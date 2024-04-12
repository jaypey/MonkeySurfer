#ifndef MENUAIDE_H
#define MENUAIDE_H

#include <QPixmap>
#include <QGuiApplication>
#include <QScreen>
#include <QGraphicsTextItem>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QHBoxLayout>
#include <QTimer>

class Menu;


class MenuAide : public QWidget
{
	Q_OBJECT

public:
	explicit MenuAide(Menu* m);
	~MenuAide();

	void startTimer();

public slots:
	void update();

private:
	Menu* _m;
	QTimer* _timer;
	QGraphicsScene* _scene;
	QGraphicsView* _view;
	QPushButton* _exitButton;
	QWidget* buttonContainer;
	QHBoxLayout* buttonLayout;
	QGraphicsPixmapItem* _background;
	QGraphicsPixmapItem* _panel;
	QGraphicsTextItem* _titre;
	QGraphicsPixmapItem* _singe;
	QGraphicsPixmapItem* _ruche;
	QGraphicsPixmapItem* _serpent;
	QGraphicsPixmapItem* _harpie;
	QGraphicsPixmapItem* _bouclier;
	QGraphicsPixmapItem* _banane;
	QGraphicsPixmapItem* _piece;
	QGraphicsTextItem* _singeTxt;
	QGraphicsTextItem* _rucheTxt;
	QGraphicsTextItem* _serpentTxt;
	QGraphicsTextItem* _harpieTxt;
	QGraphicsTextItem* _bouclierTxt;
	QGraphicsTextItem* _bananeTxt;
	QGraphicsTextItem* _pieceTxt;


	void setupUI();

signals:
	void retourVersMenu();
};

#endif // !MENUAIDE_H



