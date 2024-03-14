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
	int getPointageJoueur();
	int getPiecesJoueur();
	void restartJeu(Joueur* j);

	std::vector<ElementJeu*> getElements() const;
	std::chrono::steady_clock::time_point getLastUpdate();
	JsonSerial* getJsonSerial();
private:
	void updateJeu();
	void updateJoueur();
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

	JsonSerial* _jsonserial; // pour les commandes de manette
};

#endif // !JEU_H
