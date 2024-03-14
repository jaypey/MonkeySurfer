#ifndef HARPIEFEROCE_H
#define HARPIEFEROCE_H
#include "obstacle.h"

#define GAUCHE 0
#define DROITE 1

class HarpieFeroce : public Obstacle
{
public:
	HarpieFeroce();
	~HarpieFeroce();
	void deplacement();
	int getDirection();

private:
	int direction;

};

#endif //HARPIEFEROCE_H