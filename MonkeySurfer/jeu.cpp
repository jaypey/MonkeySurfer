#include "jeu.h"
#include <conio.h>

Jeu::Jeu(Joueur* j)
{
	_joueur = j;
	_vitesse = 1000;
}

Jeu::~Jeu() {}

void Jeu::debuterPartie()
{
	_gameOver = false;
	_mainThread = std::thread(&Jeu::updateJeu, 1);
}

std::vector<Obstacle> Jeu::getObstacles() const
{
	return _obstacles;
}

std::vector<Collectible> Jeu::getItems() const
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
	/*for (int i = 0; i < _obstacles.size(); i++)
	{
		_obstacles[i]->
	}*/
}

void Jeu::avancerCase()
{
}
