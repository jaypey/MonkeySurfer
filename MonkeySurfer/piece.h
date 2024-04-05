#ifndef PIECE_H
#define PIECE_H

#include "collectible.h"

class Piece : public ElementJeu
{
public:
    Piece();
    ~Piece();

    virtual bool collision(Joueur& _joueur);
    void appliquerEffet(Joueur& joueur);
    void afficherInfo() const;
};

#endif // !PIECE_H
