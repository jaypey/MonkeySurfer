#ifndef JEU_H
#define JEU_H
#include <vector>
#include "elementaleatoire.h"
#include "joueur.h"


class Jeu
{
public:
	Jeu(Joueur*);
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
};

#endif // !JEU_H
