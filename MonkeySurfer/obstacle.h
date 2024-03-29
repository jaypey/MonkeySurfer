#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "elementjeu.h"

class Obstacle : public ElementJeu
{
public:
	Obstacle();
	virtual ~Obstacle();

	virtual bool collision(Joueur& _joueur) = 0;
	virtual void afficherInfo() const = 0;

};

#endif // !OBSTACLE_H
