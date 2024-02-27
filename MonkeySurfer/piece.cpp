#include "piece.h"

Piece::Piece()
{
	setID(PIECE);
}

Piece::~Piece()
{
}

void Piece::appliquerEffet(Joueur& joueur)
{
	//ajouter une piece au joueur
}

void Piece::afficherInfo() const
{
	std::cout << "Une pièce de plus" << std::endl;
}
