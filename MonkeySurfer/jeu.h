#include "joueur.h"
#include <queue>
#include "obstacle.h"
#include "piece.h"
#include "collectible.h"
#include <thread>
#include "elementaleatoire.h"
#ifndef JEU_H
#define JEU_H

class Jeu
{
public:
	Jeu(Joueur*);
	~Jeu();

	void debuterPartie();
	Coordonnee getPositionJoueur();
	bool isGameOver();

	std::vector<ElementJeu*> getElements() const;
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
	std::thread _mainThread;
	bool _gameOver;
	int _vitesse;
};

#endif // !JEU_H
