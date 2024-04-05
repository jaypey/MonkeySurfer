#ifndef PROJECTILE_H
#define PROJECTILE_H
#include "obstacle.h"

class Projectile : public Obstacle
{
public:
    Projectile();
    ~Projectile();
    bool collisionAvecJoueur(Coordonnee p_joueur);
    void tombe();
    void afficherInfo() const;
};

#endif //!PROJECTILE_H
