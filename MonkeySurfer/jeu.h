#include "joueur.h"
#include <queue>
#include "obstacle.h"
#include "piece.h"
#include "collectible.h"
#include <thread>
#ifndef JEU_H
#define JEU_H

class Jeu
{
public:
	Jeu(Joueur*);
	~Jeu();

	void debuterPartie();

	std::vector<Obstacle> getObstacles() const;
	std::vector<Collectible> getItems() const;
private:
	void updateJeu();
	void updateJoueur();
	void validerCollision();
	void avancerCase();
private:
	std::chrono::steady_clock::time_point _lastUpdate;
	
	Joueur* _joueur; //Ajuster pour multijoueur éventuellement
	std::vector<Obstacle> _obstacles;
	std::vector<Collectible> _items;
	std::thread _mainThread;
	bool _gameOver;
	int _vitesse;
};

#endif // !JEU_H
