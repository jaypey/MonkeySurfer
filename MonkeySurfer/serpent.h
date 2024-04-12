#ifndef SERPENT_H
#define SERPENT_H
#include "obstacle.h"

class Serpent : public Obstacle
{
public:
    Serpent();
    ~Serpent();
    virtual bool collision(Joueur& _joueur);
    void attraperJoueur(Joueur& p_joueur);
    int getHp();
    int getHpMax();
    void recoitCoup(Joueur& p_joueur);
    void mourir(Joueur& p_joueur);
    void afficherInfo() const;

private:
    int hp;
    int hpmax;
};

#endif //SERPENT_H