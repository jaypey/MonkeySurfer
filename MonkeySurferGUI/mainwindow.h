#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>

class MonkeySurferMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MonkeySurferMainWindow();

private slots:
	void demarrerPartie();
	void demarrerPartieMulti();
	void afficherSkins();
	void afficherAide();
	void quitter();

private:
	QGridLayout* layout;
	QPushButton* btnDemarrer;
	QPushButton* btnDemarrerMulti;
	QPushButton* btnAfficherSkins;
	QPushButton* btnAfficherAide;
	QPushButton* btnQuitter;
};


#endif // !MAINWINDOW_H
