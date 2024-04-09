#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>

class MonkeySurferMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MonkeySurferMainWindow();

private slots:
	void demarrerPartie();
	void demarrerPartieMulti();
	void afficherSkins();
	void afficherAide();
	void quitter();

private:
	QWidget* m_centralWidget;
	QGridLayout* m_layout;
	QPushButton* m_btnDemarrer;
	QPushButton* m_btnDemarrerMulti;
	QPushButton* m_btnAfficherSkins;
	QPushButton* m_btnAfficherAide;
	QPushButton* m_btnQuitter;
};


#endif // !MAINWINDOW_H
