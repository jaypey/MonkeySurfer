#ifndef HARPIEFEROCE_H
#define HARPIEFEROCE_H
#include "obstacle.h"
#include "direction.h"

class HarpieFeroce : public Obstacle
{
public:
	HarpieFeroce();
	~HarpieFeroce();
	void deplacement();
	int getDirection();
	virtual void collision(Joueur& _joueur);
	void afficherInfo() const;

private:
	int direction;

};

#endif //HARPIEFEROCE_H