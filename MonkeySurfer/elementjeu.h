#ifndef ELEMENTJEU_H
#define ELEMENTJEU_H

#include <iostream>
#include "aleatoire.h"
#include "coordonnee.h"

#define OBSTACLE_FIXE        0
#define OBSTACLE_TOMBANT    1
#define BANANE                2
#define BOUCLIER            3
#define PIECE                4
#define HARPIE                5
#define SERPENT                6

#define HAUTEUR_GENERATION    25

class Joueur;

class ElementJeu
{
public:
    ElementJeu();
    virtual ~ElementJeu();

    virtual bool collision(Joueur& _joueur) = 0; // true si on delete l'element de la liste d'element de la classe jeu
    virtual void afficherInfo() const = 0;

    int getID();
    void setID(int p_id);

    Coordonnee getPosition();
    void setPosition(Coordonnee);

protected:
    RandomGenerator generateur;

private:
    int id;
    Coordonnee position;
};

#include "joueur.h"

#endif // !ELEMENTJEU_H

