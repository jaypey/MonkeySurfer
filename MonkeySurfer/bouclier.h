#ifndef BOUCLIER_H
#define BOUCLIER_H
#include "collectible.h"

class Bouclier : public Collectible
{
public:
    Bouclier();
    ~Bouclier();

    virtual bool collision(Joueur& _joueur);
    virtual void stocker(Joueur& joueur);
    virtual void appliquerEffet(Joueur& joueur);
    virtual void afficherInfo() const;

private:
    std::chrono::steady_clock::time_point lastUpdateBouclier;
};

#endif // !BOUCLIER_H
