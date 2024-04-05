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
    bool getAvertissement();
    virtual bool collision(Joueur& _joueur);
    bool finDeParcours();
    void afficherInfo() const;

private:
    Direction direction;
    bool avertissement; // Point d'exclamation avant que l'harpie apparaisse
};

#endif //HARPIEFEROCE_H