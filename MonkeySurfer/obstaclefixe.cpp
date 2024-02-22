#include "obstaclefixe.h"

ObstacleFixe::ObstacleFixe()
{
}

ObstacleFixe::~ObstacleFixe()
{
}

void ObstacleFixe::collisionAvecJoueur()
{
	//fonction appelé lors de la collision
	//bloque le joueur?
}

void ObstacleFixe::afficherInfo() const
{
	std::cout << "Un obstacle fixe est apparu" << std::endl;
}
