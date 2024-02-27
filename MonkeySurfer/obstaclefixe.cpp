#include "obstaclefixe.h"

ObstacleFixe::ObstacleFixe()
{
	setID(OBSTACLE_FIXE);
	setPosition({generateur.random(0, 4, rand() % 1000), 0});
}

ObstacleFixe::~ObstacleFixe()
{
}

bool ObstacleFixe::collisionAvecJoueur(Coordonnee p_joueur)
{
	if (p_joueur == getPosition())
	{
		return true;
	}
	return false;
}

void ObstacleFixe::afficherInfo() const
{
	std::cout << "Un obstacle fixe est apparu" << std::endl;
}
