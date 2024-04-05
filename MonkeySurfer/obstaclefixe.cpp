#include "obstaclefixe.h"

ObstacleFixe::ObstacleFixe()
{
	setID(OBSTACLE_FIXE);
	setPosition({generateur.random(0, 4, rand() % 1000), 0});
}

ObstacleFixe::~ObstacleFixe()
{
}


bool ObstacleFixe::collision(Joueur& _joueur)
{
	if (_joueur.getEtatBouclier())
	{
		_joueur.setEtatBouclier(false);   // Desactive le bouclier
	}
	else
	{
		_joueur.isDead();
	}
	delete this;
	return true;
}

void ObstacleFixe::afficherInfo() const
{
	std::cout << "Un obstacle fixe est apparu" << std::endl;
}
