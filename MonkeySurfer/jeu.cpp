#include "jeu.h"
#include <conio.h>
#include "affichageconsole.h"

Jeu::Jeu(Joueur* j)
{
	_joueur = j;
	_vitesse = 1000;
	_isStarted = false;
	_gameOver = false;
}

Jeu::~Jeu() {}

void Jeu::debuterPartie()
{
	_isStarted = true;
	updateJeu();
}

Coordonnee Jeu::getPositionJoueur()
{
	return _joueur->getPosition();
}

int Jeu::getPointageJoueur() {
	return _joueur->getScore();
}

int Jeu::getPiecesJoueur()
{
	return _joueur->getPiece();
}

void Jeu::restartJeu(Joueur* j)
{
	_joueur = j;
	_vitesse = 1000;
	_isStarted = false;
	_gameOver = false;
	_elements.clear();
}

bool Jeu::isGameOver()
{
	return _gameOver;
}

bool Jeu::isStarted()
{
	return _isStarted;
}

std::vector<ElementJeu*> Jeu::getElements() const
{
	return _elements;
}

std::chrono::steady_clock::time_point Jeu::getLastUpdate() {
	return _lastUpdate;
}

void Jeu::updateJeu()
{
	if (!_gameOver)
	{
		_vitesse = 1000 - (pow(_joueur->getScore(), 2) / 1000);
		_joueur->compteurPointage();
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
	Coordonnee courante = _joueur->getPosition();
	if (!_kbhit())
	{
		return;
	}
	char c = _getch();
	if (c == 224) c = _getch();
	if (c == 75) {
		_joueur->Left();
	}
	else if (c == 77) {
		_joueur->Right();
	}

}

void Jeu::validerCollision()
{

	for (int i = 0; i < _elements.size(); i++)
	{
		if (_elements[i]->getPosition() == _joueur->getPosition()) {
			switch (_elements[i]->getID())
			{
			case OBSTACLE_FIXE:
				_gameOver = true;
				break;
			case PIECE:
				_joueur->ramasserPiece();
				_elements.erase(_elements.begin() + i);
			default:
				break;
			}
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
		courant.y++;
		if (courant.y > HAUTEUR_GENERATION)
		{
			_elements.erase(_elements.begin() + i);
		}
		_elements[i]->setPosition(courant);
	}
	ElementJeu* element = _generateur.getRandomObstacle();
	if (rand() % 4 == 2)
	{
		ElementJeu* piece = new Piece();
		if (!(piece->getPosition() == element->getPosition()))
		{
			_elements.push_back(piece);
		}
		else {
			delete piece;
		}
	}
	_elements.push_back(element);
}
