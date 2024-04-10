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

class GameOverMenuGui : public QMainWindow
{
public:
	GameOverMenuGui(Jeu* j);

	void sceneAjouter(QGraphicsScene* scene);
	void setVisible(bool visible);
	void setChoixOption(int choix);

	void setScore();
	void setPiece();

	void btnMenu();
	void btnRejouer();

private:
	QWidget* _centralWidget;
	QGraphicsTextItem* _score;
	QGraphicsTextItem* _pieces;
	QGraphicsRectItem* _choix;
	QGraphicsPixmapItem* _cadre;
	QGraphicsTextItem* _gameOverTxt;
	QPushButton* _retourMenuBtn;
	QPushButton* _rejouerBtn;
	QWidget* _widgetBtns;
	QGridLayout* _layout;

	Jeu* _j;

};

#endif // GAMEOVERMENUHUI_H