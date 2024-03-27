#ifndef JEU_H
#define JEU_H

#include <vector>
#include "elementaleatoire.h"
#include "joueur.h"
#include "jsonserial.h"

class Jeu
{
public:
	Jeu(Joueur*, JsonSerial*);
	~Jeu();

	void debuterPartie();
	Coordonnee getPositionJoueur();
	bool isGameOver();
	bool isStarted();
	bool isPaused();
	bool isQuitting(); //Requete du jeu, lue par le menu pour afficher le menu
	int getPointageJoueur();
	charInventaire getCharInventaire();
	int getPiecesJoueur();
	int getPauseOption();
	void setPause(bool pause);
	void restartJeu(Joueur* j);

	std::vector<ElementJeu*> getElements() const;
	std::chrono::steady_clock::time_point getLastUpdate();
	JsonSerial* getJsonSerial();
private:
	void updateJeu();
	void updateJoueur();
	void updatePause();
	void updateGameOver();
	void validerCollision();
	void avancerCase();
private:
	std::chrono::steady_clock::time_point _lastUpdate;
	
	Joueur* _joueur; //Ajuster pour multijoueur éventuellement
	GenerateurItem _generateur;
	std::vector<ElementJeu*> _elements;
	bool _gameOver;
	int _vitesse;
	bool _isStarted;
	bool _isQuitting;

	bool _modePause;
	int _pauseOption;

	JsonSerial* _jsonserial; // pour les commandes de manette
};

#endif // !JEU_H
