#ifndef JOUEUR_H
#define JOUEUR_H

#include <chrono>
#include "coordonnee.h"

class Joueur
{
public:
	Joueur();
	~Joueur();
	int getPiece();
	int getScore();
	void ramasserPiece();
	void compteurPointage();
	bool ajouterInventaire(int idObj);
	bool echangerInventaire();
	int useObjet(int idObj);

	Coordonnee getPosition()const;
	void setPosition(const Coordonnee& pos);
	bool up();
	bool down();
	bool Right();
	bool Left();
	
private:
	Coordonnee position;
	int nbPieces;
	int score;
	int nbObjets;
	int inventaire[2];
	std::chrono::steady_clock::time_point lastUpdate;
};

#endif // !JOUEUR_H
