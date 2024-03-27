#ifndef JOUEUR_H
#define JOUEUR_H

#include <chrono>
#include "coordonnee.h"
#include "elementjeu.h"
#include "skin.h"

struct charInventaire {
	char item1;
	char item2;
};

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
	int getNbItem();
	bool ajouterInventaire(Collectible *powerUp);
	charInventaire getCharInventaire();
	void setCharInventaire(charInventaire c);

	bool echangerInventaire();
	void useObjet();
	void enleverObjet();
	
	void switchEtatBouclier();
	void setEtatBouclier(bool etat);
	bool getEtatBouclier();

	void switchEtatEffetBanane();
	void setEtatEffetBanane(bool etat);
	bool getEtatEffetBanane();

	void immobiliser(bool etat);
	bool isFree();

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
	charInventaire charInv;
	std::chrono::steady_clock::time_point lastUpdate;
};

#include "collectible.h"

#endif // !JOUEUR_H
