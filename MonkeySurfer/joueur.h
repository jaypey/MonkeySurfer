#ifndef JOUEUR_H
#define JOUEUR_H

#include <chrono>
#include "coordonnee.h"
#include "elementjeu.h"
#include "skin.h"

class Collectible;
class Joueur
{
public:
	Joueur();
	~Joueur();

	void reset();

	int getPiece();
	void addPiece(int n);
	int getScore();
	void ramasserPiece();
	void compteurPointage();
	bool ajouterInventaire(Collectible *powerUp);
	bool echangerInventaire();
	Collectible* useObjet();
	void enleverObjet();
	
	void switchEtatBouclier();
	void setEtatBouclier(bool etat);
	bool getEtatBouclier();

	void switchEtatEffetBanane();
	void setEtatEffetBanane(bool etat);
	bool getEtatEffetBanane();

	void immobiliser(bool etat);

	bool getVie();
	void isDead();

	Coordonnee getPosition() const;
	void setPosition(const Coordonnee &pos);
	bool up();
	bool down();
	bool Right();
	bool Left();

private:
	Coordonnee position;
	bool bouclierActif;
	bool effetBanane;
	bool immobilise;
	bool enVie;

	int nbPieces;
	int score;
	int nbObjets;
	Collectible* inventaire[2];
	std::chrono::steady_clock::time_point lastUpdate;
};

#include "collectible.h"

#endif // !JOUEUR_H
