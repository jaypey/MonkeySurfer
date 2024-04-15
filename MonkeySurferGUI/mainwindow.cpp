#include "mainwindow.h"

#include <QAction>
#include <QInputDialog>
#include <QMenu>
#include <QMenuBar>

MonkeySurferMainWindow::MonkeySurferMainWindow(AffichageGUI* jeu, Menu* menu)
{
	m_centralWidget = new QStackedWidget(this);
	m_aide = new MenuAide(menu);
	m_mainWidget = new QWidget(m_centralWidget);
	m_menu = menu;
	m_jeu = jeu;
	m_multijoueurLobby = new MultijoueurLobby(menu, jeu);
	Skin* skins = menu->getSkins();
	m_skinShop = new SkinShop(m_jeu->getjeu()->getJoueur(), skins, m_menu);

	m_multijoueurLobby->hide();
	this->setCentralWidget(m_centralWidget);
	m_layout = new QGridLayout(this);
	m_layout->setContentsMargins(200, 0, 200, 0);
	m_mainWidget->setLayout(m_layout);
	m_centralWidget->addWidget(m_mainWidget);
	m_centralWidget->addWidget(m_skinShop);
	m_centralWidget->addWidget(m_multijoueurLobby);
	m_centralWidget->addWidget(m_aide);

	m_centralWidget->setCurrentIndex(0);

	QPixmap bkgnd(":\\sprites\\Background\\Background\\Background.png");
	int width = bkgnd.width();
	int height = bkgnd.height();
	int cropHeight = 1080;

	// Calculate the y-coordinate to start cropping from
	int startY = height - cropHeight;
	bkgnd = bkgnd.copy(0, startY, width, cropHeight);
	QPalette palette;
	bkgnd = bkgnd.scaledToWidth(WINDOW_SIZE_X);
	bkgnd = bkgnd.scaledToHeight(WINDOW_SIZE_Y);
	palette.setBrush(QPalette::Window, bkgnd);
	this->setPalette(palette);

	QString str = "QPushButton:focus{color: #344f3e;} QPushButton:hover{color: #344f3e; background: none; border: none;}"
		"QPushButton {"
		"font-size: 40px;"
		"background: none; border: none;"
		"color: #ceb597;"
		" height: 30px;}"
		"QPushButton:pressed {background: none; border: none;"
		"color: #32a852;}";


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
	m_btnDemarrerMulti->setStyleSheet(str);
	connect(m_btnDemarrerMulti, &QPushButton::released, this, &MonkeySurferMainWindow::demarrerPartieMulti);
	m_layout->addWidget(m_btnDemarrerMulti, 2, 0, Qt::AlignCenter);

	m_btnAfficherSkins = new MenuButton("Skins", this);
	m_btnAfficherSkins->setStyleSheet(str);
	connect(m_btnAfficherSkins, &QPushButton::released, this, &MonkeySurferMainWindow::afficherSkins);
	m_layout->addWidget(m_btnAfficherSkins, 3, 0, Qt::AlignCenter);

	m_btnAfficherAide = new MenuButton("Aide", this);
	m_btnAfficherAide->setStyleSheet(str);
	connect(m_btnAfficherAide, &QPushButton::released, this, &MonkeySurferMainWindow::afficherAide);
	m_layout->addWidget(m_btnAfficherAide, 4, 0, Qt::AlignCenter);

	m_btnQuitter = new MenuButton("Quitter", this);
	m_btnQuitter->setStyleSheet(str);
	connect(m_btnQuitter, &QPushButton::released, this, &QApplication::quit);
	m_layout->addWidget(m_btnQuitter, 5, 0, Qt::AlignCenter);

	connect(m_skinShop, SIGNAL(retourMenu()), this, SLOT(handleRetourMenu()));
	connect(m_multijoueurLobby, SIGNAL(retourMenu()), this, SLOT(handleRetourMenu()));
	connect(m_aide, SIGNAL(retourVersMenu()), this, SLOT(handleRetourMenu()));

	m_updateTimer = new QTimer;
	QObject::connect(m_updateTimer, SIGNAL(timeout()), this, SLOT(updateMenuSelection()));
	m_updateTimer->start(1000 / FPS);

	// Menu pour le son (modifier volume + couper le son)
	QString qssMenu = "QMenu, QMenuBar {font-size: 20px; color: #ceb597;}";
	QMenu* menuSon = new QMenu("&Son");
	menuSon->setStyleSheet(qssMenu);
	menuBar()->setStyleSheet(qssMenu);
	QAction* modifVolume = new QAction("Modifier Volume");
	QAction* couperSon = new QAction("Couper son");
	couperSon->setCheckable(true);
	menuSon->addAction(modifVolume);
	menuSon->addAction(couperSon);
	menuBar()->addMenu(menuSon);

	connect(modifVolume, SIGNAL(triggered()), this, SLOT(modifierVolumeDialog()));		// Dialog box pour modifier volume
	connect(this, SIGNAL(modifierVolume(int)), m_jeu, SLOT(modifierVolume(int)));	// Volume voulu envoye a AffichageGUI
	connect(couperSon, SIGNAL(toggled(bool)), m_jeu, SLOT(couperSon(bool)));			// Couper son completement
}

void MonkeySurferMainWindow::updateMenuSelection()
{
	m_menu->update();
	m_btnDemarrer->setText("Jouer");
	m_btnDemarrerMulti->setText("Multijoueur");
	m_btnAfficherSkins->setText("Skins");
	m_btnAfficherAide->setText("Aide");
	m_btnQuitter->setText("Quitter");

	switch (m_menu->getChoixMenu())
	{
	case 0:
		m_btnDemarrer->setText("> Jouer");
		m_btnDemarrer->setFocus(Qt::FocusReason::MouseFocusReason);
		if (m_menu->getEtat() == Menu::EtatMenu::JEU) {
			m_btnDemarrer->click();
		}
		break;
	case 1:
		m_btnDemarrerMulti->setText("> Multijoueur");
		m_btnDemarrerMulti->setFocus(Qt::FocusReason::MouseFocusReason);
		if (m_menu->getEtat() == Menu::EtatMenu::MULTIJOUEUR)
		{
			m_btnDemarrerMulti->click();
		}
		break;
	case 2:
		m_btnAfficherSkins->setText("> Skins");
		m_btnAfficherSkins->setFocus(Qt::FocusReason::MouseFocusReason);
		if (m_menu->getEtat() == Menu::EtatMenu::SKINS) {
			m_btnAfficherSkins->animateClick();
		}
		break;
	case 3:
		m_btnAfficherAide->setText("> Aide");
		m_btnAfficherAide->setFocus(Qt::FocusReason::MouseFocusReason);
		if (m_menu->getEtat() == Menu::EtatMenu::AIDE) {
			m_btnAfficherAide->animateClick();
		}
		break;
	case 4:
		m_btnQuitter->setText("> Quitter");
		m_btnQuitter->setFocus(Qt::FocusReason::MouseFocusReason);
		if (m_menu->getEtat() == Menu::EtatMenu::QUITTER) {
			m_btnQuitter->animateClick();
		}
		break;
	}

	//if (m_menu->getEtat() == Menu::EtatMenu::SKINS) {
	//	afficherSkins();
	//}
	//else if (m_menu->getEtat() == Menu::EtatMenu::MULTIJOUEUR) {
	//	demarrerPartieMulti();
	//}
	//else if (m_menu->getEtat() == Menu::EtatMenu::AIDE)
	//{
	//	afficherAide();
	//}
}

void MonkeySurferMainWindow::modifierVolumeDialog() {
	bool ok;
	int volume = QInputDialog::getInt(this, "Choisir le volume", "Volume:", m_jeu->getVolume(), 0, 100, 0, &ok);

	// Volume de 0 a 100, convertit en float de 0.0 a 1.0
	if (ok)
		emit modifierVolume(volume);
}

void MonkeySurferMainWindow::handleRetourMenu()
{
	m_centralWidget->setCurrentIndex(0);
	show();
	m_updateTimer->start(1000 / FPS);
	m_menu->setEtat(Menu::EtatMenu::PRINCIPAL);
}

void MonkeySurferMainWindow::demarrerPartie() {
	m_updateTimer->stop();
	m_menu->setEtat(Menu::EtatMenu::JEU);

	// Reset + afficher jeu
	m_jeu->reset();
	m_jeu->getjeu()->getJoueur()->reset();
	m_jeu->getjeu()->restartJeu(m_jeu->getjeu()->getJoueur());
	m_jeu->showFullScreen();
	hide();
}

void MonkeySurferMainWindow::demarrerPartieMulti()
{
	m_updateTimer->stop();
	std::string ipAddress = (QInputDialog::getText(nullptr, "Connexion multijoueur", "Veuillez entrer l'adresse du serveur")).toStdString();
	m_menu->connectNetwork(ipAddress);
	m_centralWidget->setCurrentIndex(2);
	m_multijoueurLobby->startUpdateLoop();
}

void MonkeySurferMainWindow::afficherSkins()
{
	m_centralWidget->setCurrentIndex(1);
	m_menu->setEtat(Menu::EtatMenu::SKINS);
	m_updateTimer->stop();
	m_skinShop->startTimer();
}

void MonkeySurferMainWindow::afficherAide()
{
	m_centralWidget->setCurrentIndex(3);
	m_menu->setEtat(Menu::EtatMenu::AIDE);
	m_updateTimer->stop();
	m_aide->startTimer();
}

