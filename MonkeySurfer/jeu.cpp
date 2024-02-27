#include "jeu.h"
#include <conio.h>
#include "joueur.h"
#include "affichageconsole.h"

Jeu::Jeu(Joueur* j)
{
	_joueur = j;
	_vitesse = 1000;
}

Jeu::~Jeu() {}

void Jeu::debuterPartie()
{
	_gameOver = false;
	_mainThread = std::thread(&Jeu::updateJeu, this);
}

Coordonnee Jeu::getPositionJoueur()
{
	return _joueur->getPosition();
}

bool Jeu::isGameOver()
{
	return _gameOver;
}

std::vector<ElementJeu*> Jeu::getElements() const
{
	return _elements;
}

void Jeu::updateJeu()
{
	while (!_gameOver)
	{
		validerCollision();
		updateJoueur();
		auto now = std::chrono::steady_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastUpdate);
		if (elapsed.count() >= _vitesse) {
			_lastUpdate = now;
			avancerCase();
		}
	}
}

void Jeu::updateJoueur()
{
	char c = _getch();
	Coordonnee courante = _joueur->getPosition();
	if (c == 224) c = _getch();
	if (c == 75) { //LEFT
		if (courante.x > 0) {
			courante.x++;
			_joueur->setPosition(courante);

		}
	}
	else if (c == 77) { //RIGHT
		if (courante.x <= 3) {
			courante.x--;
			_joueur->setPosition(courante);
		}
	}

}

void Jeu::validerCollision()
{

	for (int i = 0; i < _elements.size(); i++)
	{
		if (_elements[i]->getPosition() == _joueur->getPosition()) {
			return;
		}
	}
}

void Jeu::avancerCase()
{
	Coordonnee courant;

	for (int i = 0; i < _elements.size(); i++)
	{
		courant = _elements[i]->getPosition();
		courant.y--;
		if (courant.y - 1 < 0)
		{
			_elements.erase(_elements.begin() + i);
		}
		_elements[i]->setPosition(courant);
	}
	
	_elements.push_back(_generateur.getRandomObstacle());
}
