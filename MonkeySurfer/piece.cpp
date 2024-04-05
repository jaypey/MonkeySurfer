#include "piece.h"

Piece::Piece()
{
	setID(PIECE);
	setPosition({ generateur.random(0, 4, rand() % 1000), 0 });
}

Piece::~Piece()
{
}

bool Piece::collision(Joueur& _joueur)
{
	appliquerEffet(_joueur);
	delete this;
	return true;
}

void Piece::appliquerEffet(Joueur& joueur)
{
	joueur.ramasserPiece();
}

void Piece::afficherInfo() const
{
	std::cout << "Une piece de plus" << std::endl;
}
