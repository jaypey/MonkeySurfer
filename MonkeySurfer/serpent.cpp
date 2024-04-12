#include "serpent.h"

Serpent::Serpent()
{
    setID(SERPENT);
    hp = generateur.random(60, 100, rand() % 1000);
    hpmax = hp;
    setPosition({ generateur.random(0, 4, rand() % 1000) , getPosition().y });
}

Serpent::~Serpent()
{
}

bool Serpent::collision(Joueur& _joueur)
{
    if (_joueur.getEtatBouclier())
    {
        _joueur.setEtatBouclier(false);
    }
    else 
    {
        attraperJoueur(_joueur);
    }
    return true;
}

void Serpent::attraperJoueur(Joueur& p_joueur)
{
    p_joueur.immobiliser(true);
    p_joueur.setSerpent(this);
}

int Serpent::getHp()
{
    return hp;
}

int Serpent::getHpMax() {
    return hpmax;
}

void Serpent::recoitCoup(Joueur& p_joueur)
{
    hp--;
    if (hp <= 0)
    {
        mourir(p_joueur);
    }
}

void Serpent::mourir(Joueur& p_joueur)
{
    p_joueur.ramasserPiece();        //Donne 20 pts au joueur pour tuer un serpent
    p_joueur.ramasserPiece();
    p_joueur.immobiliser(false);
    p_joueur.setSerpent(nullptr);
}

void Serpent::afficherInfo() const
{
    std::cout << "Un serpent est apparu" << std::endl;
}