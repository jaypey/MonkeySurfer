#ifndef OBSTACLEFIXE_H
#define OBSTACLEFIXE_H
#include "obstacle.h"

class ObstacleFixe : public Obstacle
{
public:
	ObstacleFixe();
	~ObstacleFixe();

	bool collisionAvecJoueur(Coordonnee p_joueur);
	void afficherInfo() const;
};


#endif // !OBSTACLEFIXE_H