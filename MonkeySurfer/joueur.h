#ifndef JOUEUR_H
#define JOUEUR_H

class Joueur
{
public:
	Joueur();
	~Joueur();

	int getPiece();
	int getScore();

	void ramasserPiece();
	void conteurPointage();
	void ajouterInventaire();
	void echangerInventaire();
	void useObjet();
	
private:

	int nbPieces;
	int score;
	int nbObjets;
};

#endif // !JOUEUR_H
