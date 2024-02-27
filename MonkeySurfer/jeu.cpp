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

std::vector<Obstacle*> Jeu::getObstacles() const
{
	return _obstacles;
}

std::vector<Collectible*> Jeu::getItems() const
{
	return _items;
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
	//if (c == 75)        _joueur->coordonee; // LEFT
	//else if (c == 77)   _joueur->coordonee;  // RIGHT

}

void Jeu::validerCollision()
{
	for (int i = 0; i < _obstacles.size(); i++)
	{
		if (_obstacles[i]->getPosition() == _joueur->getPosition()) {
			_gameOver = true;
			return;
		}
	}
	for (int i = 0; i < _items.size(); i++)
	{
		if (_items[i]->getPosition() == _joueur->getPosition()) {
			/*_joueur->inventaire */ //Ajouter l'objet dans l'inventaire
			return;
		}
	}
}

void Jeu::avancerCase()
{
	Coordonnee courant;

	for (int i = 0; i < _obstacles.size(); i++)
	{
		courant = _obstacles[i]->getPosition();
		courant.y--;
		if (courant.y - 1 < 0)
		{
			_obstacles.erase(_obstacles.begin() + i);
		}
		_obstacles[i]->setPosition(courant);
	}
	for (int i = 0; i < _items.size(); i++)
	{
		courant = _items[i]->getPosition();
		if (courant.y-1 < 0)
		{
			_items.erase(_items.begin() + i);
		}
		courant.y--;
		_items[i]->setPosition(courant);
	}
	_generateur.getRandomObstacle();
}
