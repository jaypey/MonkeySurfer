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
	_isAttacking = false;

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

charInventaire Jeu::getCharInventaire()
{
	return _joueur->getCharInventaire();
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

bool Jeu::isStuck()
{
	return !_joueur->isFree();
}

bool Jeu::isProtected()
{
	return _joueur->getEtatBouclier();
}

bool Jeu::isBoosted()
{
	return _joueur->getEtatEffetBanane();
}

bool Jeu::isAttacking()
{
	return _isAttacking;
}

void Jeu::setIsAttacking(bool attack)
{
	_isAttacking = attack;
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
		// Score
		std::string scoreStr = "Score: " + std::to_string(_joueur->getScore());
		std::string pieceStr = "Pieces: " + std::to_string(_joueur->getPiece());
		_jsonserial->lcd(scoreStr.c_str(), pieceStr.c_str());
		_joueur->compteurPointage();

		// Joueur
		_vitesse = 1000 - (pow(_joueur->getScore(), 2) / 1000);
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
	std::cout << _joueur->getNbBoost();

	// MANETTE
	if(_joueur->isFree())
	{
		if (_jsonserial->boutonAppuye(2)) {
			if (_jsonserial->joystickMaintenu(GAUCHE)) {
				_joueur->Left();
			}
			else if (_jsonserial->joystickMaintenu(DROITE)) {
				_joueur->Right();
			}
		}

		if (_jsonserial->joystickMaintenu(HAUT, true)) {
			_joueur->up();
		}

		else if (_jsonserial->joystickMaintenu(BAS, true)) {
			_joueur->down();
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

		if(_joueur->isFree() || c == 'p' || c == ' ' || c == 'x' || c == 'z')
		{
			if (c == 75) { // Fleche gauche
				_joueur->Left();
			}
			else if (c == 77) { // Fleche droite
				_joueur->Right();
			}
			else if (c == 80) { //Fleche bas
				_joueur->down();
			}
			else if (c == 72) {	//Fleche haut
				_joueur->up();
			}
			else if (c == 'p') {
				_modePause = true;
			}
			else if (c == ' ')
			{	
				_isAttacking = true;
				if (_joueur->getSerpent() != nullptr)
				{
					_joueur->getSerpent()->recoitCoup(*_joueur);
				}
				
			}
			else if (c == 'z')
			{
				_joueur->echangerInventaire();
			}
			else if (c == 'x')
			{
				_joueur->useObjet();
			}
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

	if (_jsonserial->joystickMaintenu(HAUT, true)) {
		_pauseOption--;
		if (_pauseOption < 0)
			_pauseOption = 1;
	}
	else if (_jsonserial->joystickMaintenu(BAS, true)) {
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
	std::string info = "S:" + std::to_string(_joueur->getScore()) + " P:" + std::to_string(_joueur->getPiece());
	_jsonserial->lcd("GAME OVER", info.c_str());

	// MANETTE
	if (_jsonserial->boutonAppuye(1))
		_isQuitting = true;

	// CLAVIER
	if (_kbhit()) {
		char c = _getch();
		if (c == 'q') {
			_isQuitting = true;
		}
	}
}

void Jeu::validerCollision()
{
	if (getPositionJoueur().y > 21 || getPositionJoueur().y <= 0) {
		_gameOver = true;
		return;
	}

	for (int i = 0; i < _elements.size(); i++)
	{
		if (_elements[i]->getPosition() == _joueur->getPosition()) {
			_elements[i]->collision(*_joueur);
			_elements.erase(_elements.begin() + i);
			return;
		}
		_gameOver = !_joueur->getVie();
	}
}

void Jeu::avancerCase()
{
	Coordonnee courant;

	for (int i = _elements.size()-1; i >= 0; i--)
	{
		courant = _elements[i]->getPosition();
		courant.y++;
		if (courant.y > HAUTEUR_GENERATION)
		{
			delete _elements[i];
			_elements.erase(_elements.begin() + i);
		}
		else 
		{
			_elements[i]->setPosition(courant);
		}

		if (HarpieFeroce* harpie = dynamic_cast<HarpieFeroce*>(_elements[i]))
		{
			if (harpie->finDeParcours())
			{
				delete _elements[i];
				_elements.erase(_elements.begin() + i);
			}
			else
			{
				harpie->deplacement();
			}
		}

	}

	courant = _joueur->getPosition();
	courant.y++;
	_joueur->setPosition(courant);

	ElementJeu* element = _generateur.getRandomElement();
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
