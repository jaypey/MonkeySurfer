#include "mainwindow.h"

MonkeySurferMainWindow::MonkeySurferMainWindow()
{
	m_centralWidget = new QWidget(this);
	this->setBack
	this->setCentralWidget(m_centralWidget);
	m_layout = new QGridLayout(this);
	m_centralWidget->setLayout(m_layout);

	m_btnDemarrer = new QPushButton("Jouer", this);
	connect(m_btnDemarrer, &QPushButton::released, this, &MonkeySurferMainWindow::demarrerPartie);
	m_layout->addWidget(m_btnDemarrer, 0, 0);

	m_btnDemarrerMulti = new QPushButton("Multijoueur", this);
	connect(m_btnDemarrerMulti, &QPushButton::released, this, &MonkeySurferMainWindow::demarrerPartieMulti);
	m_layout->addWidget(m_btnDemarrerMulti, 1, 0);

	m_btnAfficherSkins = new QPushButton("Skins", this);
	connect(m_btnAfficherSkins, &QPushButton::released, this, &MonkeySurferMainWindow::afficherSkins);
	m_layout->addWidget(m_btnAfficherSkins, 2, 0);

	m_btnAfficherAide = new QPushButton("Aide", this);
	connect(m_btnAfficherAide, &QPushButton::released, this, &MonkeySurferMainWindow::afficherAide);
	m_layout->addWidget(m_btnAfficherAide, 3, 0);

	m_btnQuitter = new QPushButton("Quitter", this);
	connect(m_btnQuitter, &QPushButton::released, this, &MonkeySurferMainWindow::quitter);
	m_layout->addWidget(m_btnQuitter, 4, 0);

}

void MonkeySurferMainWindow::demarrerPartie() {

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

void MonkeySurferMainWindow::quitter()
{
}
