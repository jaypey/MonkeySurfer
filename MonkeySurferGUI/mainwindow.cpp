#include "mainwindow.h"

MonkeySurferMainWindow::MonkeySurferMainWindow(QGraphicsView* jeu)
{
	m_centralWidget = new QWidget(this);
	m_jeu = jeu;
	this->setCentralWidget(m_centralWidget);
	m_layout = new QGridLayout(this);
	m_layout->setContentsMargins(200, 0, 200, 0);
	m_centralWidget->setLayout(m_layout);

	QString str = "QPushButton:hover{color: #32a150; background: none; border: none;}"
		"QPushButton {"
		"font-size: 40px;"
		"background: none; border: none;"
		"color: #32a852;"
		" height: 30px;}"
		"QPushButton:pressed {background: none; border: none;"
		"color: #1f472a;}";


	QPixmap image(":/images/monkeysurfer.png");

	m_titre = new QLabel();
	m_titre->setPixmap(image);

	m_layout->addWidget(m_titre, 0, 0, Qt::AlignCenter);

	m_btnDemarrer = new QPushButton("Jouer", this);
	m_btnDemarrer->setMaximumWidth(300);
	m_btnDemarrer->setMinimumHeight(100);
	connect(m_btnDemarrer, &QPushButton::released, this, &MonkeySurferMainWindow::demarrerPartie);
	m_btnDemarrer->setStyleSheet(str);
	m_layout->addWidget(m_btnDemarrer, 1, 0, Qt::AlignCenter);


	m_btnDemarrerMulti = new MenuButton("Multijoueur", this);
	connect(m_btnDemarrerMulti, &QPushButton::released, this, &MonkeySurferMainWindow::demarrerPartieMulti);
	m_layout->addWidget(m_btnDemarrerMulti, 2, 0, Qt::AlignCenter);

	m_btnAfficherSkins = new MenuButton("Skins", this);
	connect(m_btnAfficherSkins, &QPushButton::released, this, &MonkeySurferMainWindow::afficherSkins);
	m_layout->addWidget(m_btnAfficherSkins, 3, 0, Qt::AlignCenter);

	m_btnAfficherAide = new MenuButton("Aide", this);
	connect(m_btnAfficherAide, &QPushButton::released, this, &MonkeySurferMainWindow::afficherAide);
	m_layout->addWidget(m_btnAfficherAide, 4, 0, Qt::AlignCenter);

	m_btnQuitter = new MenuButton("Quitter", this);
	connect(m_btnQuitter, &QPushButton::released, this, &QApplication::quit);
	m_layout->addWidget(m_btnQuitter, 5, 0, Qt::AlignCenter);

}

void MonkeySurferMainWindow::demarrerPartie() {
	this->m_jeu->showFullScreen();
	this->hide();
}

void MonkeySurferMainWindow::demarrerPartieMulti()
{
}

void MonkeySurferMainWindow::afficherSkins()
{
}

void MonkeySurferMainWindow::afficherAide()
{
}
