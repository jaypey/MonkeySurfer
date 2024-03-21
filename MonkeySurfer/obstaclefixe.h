#ifndef OBSTACLEFIXE_H
#define OBSTACLEFIXE_H
#include "obstacle.h"

class ObstacleFixe : public Obstacle
{
public:
	ObstacleFixe();
	~ObstacleFixe();

	virtual void collision(Joueur& _joueur);
	void afficherInfo() const;
};


#endif // !OBSTACLEFIXE_H