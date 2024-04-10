#include "mainwindow.h"

MonkeySurferMainWindow::MonkeySurferMainWindow(QGraphicsView* jeu, Menu* menu)
{
	m_centralWidget = new QStackedWidget(this);
	m_skinShop = new SkinShop();
	m_mainWidget = new QWidget(m_centralWidget);
	m_menu = menu;
	m_jeu = jeu;
	this->setCentralWidget(m_centralWidget);
	m_layout = new QGridLayout(this);
	m_layout->setContentsMargins(200, 0, 200, 0);
	m_mainWidget->setLayout(m_layout);
	m_centralWidget->addWidget(m_mainWidget);
	m_centralWidget->addWidget(m_skinShop);
	m_centralWidget->setCurrentIndex(0);

	QString str = "QPushButton:focus{color: #c1ccba;} QPushButton:hover{color: #32a150; background: none; border: none;}"
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

	m_updateTimer = new QTimer;
	QObject::connect(m_updateTimer, SIGNAL(timeout()), this, SLOT(updateMenuSelection()));
	m_updateTimer->start(1);
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
		break;
	case 1:
		m_btnDemarrerMulti->setText("> Multijoueur");
		m_btnDemarrerMulti->setFocus(Qt::FocusReason::MouseFocusReason);
		break;
	case 2:
		m_btnAfficherSkins->setText("> Skins");
		m_btnAfficherSkins->setFocus(Qt::FocusReason::MouseFocusReason);
		break;
	case 3:
		m_btnAfficherAide->setText("> Aide");
		m_btnAfficherAide->setFocus(Qt::FocusReason::MouseFocusReason);
		break;
	case 4:
		m_btnQuitter->setText("> Quitter");
		m_btnQuitter->setFocus(Qt::FocusReason::MouseFocusReason);
		break;
	}
}

void MonkeySurferMainWindow::demarrerPartie() {
	m_updateTimer->stop();
	m_menu->setEtat(Menu::EtatMenu::JEU);
	this->m_jeu->showFullScreen();
	this->hide();
}

void MonkeySurferMainWindow::demarrerPartieMulti()
{
	m_menu->setEtat(Menu::EtatMenu::MULTIJOUEUR);
}

void MonkeySurferMainWindow::afficherSkins()
{
	m_centralWidget->setCurrentIndex(1);
	m_menu->setEtat(Menu::EtatMenu::SKINS);
}

void MonkeySurferMainWindow::afficherAide()
{
	m_menu->setEtat(Menu::EtatMenu::AIDE);
}

