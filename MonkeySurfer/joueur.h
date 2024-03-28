#ifndef JOUEUR_H
#define JOUEUR_H

#include <chrono>
#include <fstream>
#include <string>
#include "coordonnee.h"
#include "skin.h"

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
	void loadPieces();
	void compteurPointage();
	bool ajouterInventaire(int idObj);
	bool echangerInventaire();
	int useObjet(int idObj);

	Coordonnee getPosition() const;
	void setPosition(const Coordonnee &pos);
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
