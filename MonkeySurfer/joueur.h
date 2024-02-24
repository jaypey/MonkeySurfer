#ifndef JOUEUR_H
#define JOUEUR_H

#include <chrono>

class Joueur
{
public:
	Joueur();
	~Joueur();



	int getPiece();
	int getScore();

	double position();

	void ramasserPiece();
	void compteurPointage();
	void ajouterInventaire(int idObj);
	void echangerInventaire();
	void useObjet(int idObj);
	
private:

	int nbPieces;
	int score;
	int nbObjets;
	int inventaire[2];
	std::chrono::steady_clock::time_point lastUpdate;
};

#endif // !JOUEUR_H
