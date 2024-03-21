#include "piece.h"

Piece::Piece()
{
	setID(PIECE);
	setPosition({ generateur.random(0, 4, rand() % 1000), 0 });
}

Piece::~Piece()
{
}

void Piece::collision(Joueur& _joueur)
{
	appliquerEffet(_joueur);
}

void Piece::appliquerEffet(Joueur& joueur)
{
	joueur.ramasserPiece();
}

void Piece::afficherInfo() const
{
	std::cout << "Une pièce de plus" << std::endl;
}
