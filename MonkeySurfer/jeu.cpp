#include "jeu.h"
#include <conio.h>
#include "affichageconsole.h"

Jeu::Jeu(Joueur* j, JsonSerial* js)
{
	_joueur = j;
	_vitesse = 1000;
	_isStarted = false;
	_gameOver = false;
	_jsonserial = js;
	_isQuitting = false;

	_modePause = false;
	_pauseOption = 0;
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

int Jeu::getPauseOption() {
	return _pauseOption;
}

void Jeu::setPause(bool pause) {
	_modePause = pause;
	_pauseOption = 0;
}

void Jeu::restartJeu(Joueur* j)
{
	_joueur = j;
	_vitesse = 1000;
	_isStarted = false;
	_gameOver = false;
	_modePause = false;
	_isQuitting = false;
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

bool Jeu::isPaused() {
	return _modePause;
}

bool Jeu::isQuitting() {
	return _isQuitting;
}

std::vector<ElementJeu*> Jeu::getElements() const
{
	return _elements;
}

std::chrono::steady_clock::time_point Jeu::getLastUpdate() {
	return _lastUpdate;
}

JsonSerial* Jeu::getJsonSerial() {
	return _jsonserial;
}

void Jeu::updateJeu()
{
	if (!_gameOver && !_modePause)
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
	else if (_modePause) {
		updatePause();
	}
	else if (_gameOver) {
		updateGameOver();
	}
}

void Jeu::updateJoueur()
{
	// MANETTE
	if (_jsonserial->boutonAppuye(2)) {
		if (_jsonserial->joystickMaintenuX() == GAUCHE) {
			_joueur->Left();
		}
		else if (_jsonserial->joystickMaintenuX() == DROITE) {
			_joueur->Right();
		}
	}

	if (_jsonserial->boutonAppuye(1)) {
		_modePause = true;
	}

	// CLAVIER
	if (_kbhit())
	{
		char c = _getch();
		if (c == 224) c = _getch();
		if (c == 75) { // Fleche gauche
			_joueur->Left();
		}
		else if (c == 77) { // Fleche droite
			_joueur->Right();
		}
		else if (c == 'p') {
			_modePause = true;
		}
	}
}

void Jeu::updatePause() {
	// MANETTE
	if (_jsonserial->boutonAppuye(1)) {
		_modePause = false;
	}
	else if (_jsonserial->boutonAppuye(2)) {
		if (_pauseOption == 0) {
			_modePause = false;
		}
		else if (_pauseOption == 1) {
			_isQuitting = true;
		}
	}

	if (_jsonserial->joystickMaintenuY() == HAUT && _jsonserial->joystickAppuyeY()) {
		_pauseOption--;
		if (_pauseOption < 0)
			_pauseOption = 1;
	}
	else if (_jsonserial->joystickMaintenuY() == BAS && _jsonserial->joystickAppuyeY()) {
		_pauseOption++;
		if (_pauseOption > 1)
			_pauseOption = 0;
	}

	// CLAVIER
	if (_kbhit()) {
		char c = _getch();
		if (c == '1') {
			_modePause = false;
		}
		else if (c == '2') {
			_isQuitting = true;
		}
	}
}

void Jeu::updateGameOver() {
	if (_kbhit()) {
		char c = _getch();
		if (c == 'q') {
			_isQuitting = true;
		}
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
