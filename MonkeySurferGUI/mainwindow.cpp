#include "mainwindow.h"

MonkeySurferMainWindow::MonkeySurferMainWindow()
{
	m_centralWidget = new QWidget(this);

	this->setCentralWidget(m_centralWidget);
	m_layout = new QGridLayout(this);
	m_layout->setContentsMargins(200, 0, 200, 0);
	m_centralWidget->setLayout(m_layout);

	m_btnDemarrer = new QPushButton("Jouer", this);
	m_btnDemarrer->setMaximumWidth(900);
	connect(m_btnDemarrer, &QPushButton::released, this, &MonkeySurferMainWindow::demarrerPartie);
	m_layout->addWidget(m_btnDemarrer, 0, 0);

	m_btnDemarrerMulti = new QPushButton("Multijoueur", this);
	m_btnDemarrerMulti->setMaximumWidth(300);
	connect(m_btnDemarrerMulti, &QPushButton::released, this, &MonkeySurferMainWindow::demarrerPartieMulti);
	m_layout->addWidget(m_btnDemarrerMulti, 1, 0);

	m_btnAfficherSkins = new QPushButton("Skins", this);
	m_btnAfficherSkins->setMaximumWidth(300);
	m_btnAfficherSkins->setMinimumHeight
	connect(m_btnAfficherSkins, &QPushButton::released, this, &MonkeySurferMainWindow::afficherSkins);
	m_layout->addWidget(m_btnAfficherSkins, 2, 0);

	m_btnAfficherAide = new QPushButton("Aide", this);
	m_btnAfficherAide->setMaximumWidth(300);
	connect(m_btnAfficherAide, &QPushButton::released, this, &MonkeySurferMainWindow::afficherAide);
	m_layout->addWidget(m_btnAfficherAide, 3, 0);

	m_btnQuitter = new QPushButton("Quitter", this);
	m_btnQuitter->setMaximumWidth(300);
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
