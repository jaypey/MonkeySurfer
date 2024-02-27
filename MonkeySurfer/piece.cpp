#include "piece.h"

Piece::Piece()
{
	setID(PIECE);
	setPosition({ generateur.random(0, 4, rand() % 1000), 0 });
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
