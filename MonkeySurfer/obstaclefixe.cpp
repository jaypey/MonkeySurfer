#include "obstaclefixe.h"

ObstacleFixe::ObstacleFixe()
{
	setPosition({generateur.random(1, 5, 981910), HAUTEUR_GENERATION});
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
