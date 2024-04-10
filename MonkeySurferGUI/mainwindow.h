#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QApplication>
#include <QGraphicsView>
#include <QLabel>
#include <QPixMap>
#include <menubutton.h>

class MonkeySurferMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MonkeySurferMainWindow(QGraphicsView* jeu);

private slots:
	void demarrerPartie();
	void demarrerPartieMulti();
	void afficherSkins();
	void afficherAide();

private:
	QWidget* m_centralWidget;
	QGraphicsView* m_jeu;
	QGridLayout* m_layout;
	QLabel* m_titre;
	QPushButton* m_btnDemarrer;
	QPushButton* m_btnDemarrerMulti;
	QPushButton* m_btnAfficherSkins;
	QPushButton* m_btnAfficherAide;
	QPushButton* m_btnQuitter;
};


#endif // !MAINWINDOW_H
