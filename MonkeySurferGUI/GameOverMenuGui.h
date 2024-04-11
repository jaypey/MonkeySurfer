#ifndef GAMEOVERMENUHUI_H
#define GAMEOVERMENUHUI_H

#include <QGraphicsProxyWidget>
#include <QMainWindow>
#include <QGridLayout>
#include <QGuiApplication>
#include <QScreen>
#include <QPushButton>
#include <QGraphicsRectItem>
#include <qfontdatabase.h>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include "jeu.h"

class GameOverMenuGui : public QWidget
{
public:
	GameOverMenuGui(Jeu* j);

	void sceneAjouter(QGraphicsScene* scene);
	void setVisible(bool visible);
	void setChoixOption(int choix);

	void setScore();
	void setPiece();
private:
	QWidget* _centralWidget;
	QGraphicsTextItem* _score;
	QGraphicsTextItem* _pieces;
	QGraphicsTextItem* _menu;
	QGraphicsTextItem* _rejouer;
	QGraphicsRectItem* _choix;
	QGraphicsPixmapItem* _cadre;
	QGraphicsTextItem* _gameOverTxt;
	Jeu* _j;
};

#endif // GAMEOVERMENUHUI_H