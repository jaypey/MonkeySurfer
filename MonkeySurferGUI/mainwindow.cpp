#include "mainwindow.h"

MonkeySurferMainWindow::MonkeySurferMainWindow()
{
	layout = new QGridLayout(this);
	btnDemarrer = new QPushButton("Jouer", this);
	connect(btnDemarrer, &QPushButton::released, this, &MonkeySurferMainWindow::demarrerPartie);
	layout->addWidget(btnDemarrer);

	btnDemarrerMulti = new QPushButton("Multijoueur", this);
	connect(btnDemarrerMulti, &QPushButton::released, this, &MonkeySurferMainWindow::demarrerPartieMulti);
	layout->addWidget(btnDemarrerMulti);

	btnAfficherSkins = new QPushButton("Skins", this);
	connect(btnAfficherSkins, &QPushButton::released, this, &MonkeySurferMainWindow::afficherSkins);
	layout->addWidget(btnAfficherSkins);

	btnAfficherAide = new QPushButton("Aide", this);
	connect(btnAfficherSkins, &QPushButton::released, this, &MonkeySurferMainWindow::afficherAide);
	layout->addWidget(btnAfficherSkins);

	btnQuitter = new QPushButton("Quitter", this);
	connect(btnQuitter, &QPushButton::released, this, &MonkeySurferMainWindow::quitter);
	layout->addWidget(btnQuitter);

}
