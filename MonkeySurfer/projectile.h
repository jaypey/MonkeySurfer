#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "obstacle.h"

class Projectile : public Obstacle
{
public:
	Projectile();
	~Projectile();
	void collisionAvecJoueur();
	void tombe();
	void afficherInfo() const;
};

#endif //!PROJECTILE_H
