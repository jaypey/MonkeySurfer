#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QApplication>
#include <QGraphicsView>
#include <QLabel>
#include <QPixMap>
#include <QTimer>
#include <QStackedWidget>
#include <menubutton.h>
#include <affichagegui.h>
#include <skinshop.h>
#include "skinshop.h"
#include "menu.h"
#include <multijoueurlobby.h>
#include <menuaide.h>

class MonkeySurferMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MonkeySurferMainWindow(AffichageGUI* jeu, Menu* menu);

private slots:
	void demarrerPartie();
	void demarrerPartieMulti();
	void afficherSkins();
	void afficherAide();
	void updateMenuSelection();
public slots:
	void handleRetourMenu();

private:
	Menu* m_menu;
	QTimer* m_updateTimer;
	QStackedWidget* m_centralWidget;
	SkinShop* m_skinShop;
	MultijoueurLobby* m_multijoueurLobby;
	MenuAide* m_aide;
	QWidget* m_mainWidget;
	AffichageGUI* m_jeu;
	QGridLayout* m_layout;
	QLabel* m_titre;
	QPushButton* m_btnDemarrer;
	QPushButton* m_btnDemarrerMulti;
	QPushButton* m_btnAfficherSkins;
	QPushButton* m_btnAfficherAide;
	QPushButton* m_btnQuitter;
};


#endif // !MAINWINDOW_H
