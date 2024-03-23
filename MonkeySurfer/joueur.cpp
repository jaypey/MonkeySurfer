#include "Joueur.h"

Joueur::Joueur()
{
    score = 0;
    nbPieces = 0;
    nbObjets = 0;
    bouclierActif = false;
    effetBanane = false;
    immobilise = false;
    enVie = true;

    inventaire[0] = nullptr;
    inventaire[1] = nullptr;
    position.x = 2;
    position.y = 15;
    lastUpdate = std::chrono::steady_clock::now(); // moment dernier update pour score, initialiser
}

Joueur::~Joueur()
{
    delete inventaire[0]; 
    delete inventaire[1];
}

int Joueur::getPiece()
{

    return nbPieces;
}

int Joueur::getScore()
{

    return score;
}

void Joueur::ramasserPiece()
{

    nbPieces += 1;
    score += 10; // A revoir si on conserve
}

void Joueur::compteurPointage()
{

    auto maintenant = std::chrono::steady_clock::now();
    auto duree = std::chrono::duration_cast<std::chrono::seconds>(maintenant - lastUpdate).count();

    if (duree >= 1)
    {

        score += (int)duree * 10; // 10 points par seconde ecoulee
        lastUpdate = maintenant;
    }
}

bool Joueur::ajouterInventaire(Collectible* powerUp)
{

    if (nbObjets == 0)
    {
        inventaire[nbObjets++] = powerUp; // objet ajoute a la pos 0 de l'inventaire
        return true;
    }
    else if (nbObjets == 1)
    {
        inventaire[nbObjets++] = powerUp; // Objet ajoute a la pos 1 de l'inventaire
        return true;
    }
    return false;
    // Si inventaire plein, objet nest pas recupere, on pourra discuter de ce scenario en equipe
}

bool Joueur::echangerInventaire()
{

    if (nbObjets == 2)
    {
        std::swap(inventaire[0], inventaire[1]);
        return true;
    }

    return false;
}

Collectible* Joueur::useObjet()
{
    if (nbObjets > 0)
    {
        inventaire[0]->appliquerEffet(*this);
        return inventaire[0]; // retourne lobjet a la position 0, qui est lobjet utilise
    }
    return nullptr;
    
}

void Joueur::enleverObjet()
{
    std::swap(inventaire[0], inventaire[1]);
    nbObjets--;
    delete inventaire[1];
    inventaire[1] = nullptr;
}

void Joueur::switchEtatBouclier()
{
    if (bouclierActif)
    {
        bouclierActif = false;
    }
    else
    {
        bouclierActif = true;
    }
}

void Joueur::setEtatBouclier(bool etat)
{
    bouclierActif = etat;
}

bool Joueur::getEtatBouclier()
{
    return bouclierActif;
}

void Joueur::switchEtatEffetBanane()
{
    if (effetBanane)
    {
        effetBanane = false;
    }
    else
    {
        effetBanane = true;
    }
}

void Joueur::setEtatEffetBanane(bool etat)
{
    effetBanane = etat;
}

bool Joueur::getEtatEffetBanane()
{
    return effetBanane;
}

void Joueur::immobiliser(bool etat)
{
    immobilise = etat;
}

bool Joueur::getVie()
{
    return enVie;
}

void Joueur::isDead()
{
    enVie = false;
}

bool Joueur::up()
{
    if (position.y > 4)
    {

        return false;
    }

    position.y += 1;
    return true;
}

bool Joueur::down()
{
    if (position.y < 0)
    {

        return false;
    }

    position.y -= 1;
    return true;
}

bool Joueur::Right()
{
    if (position.x >= 4)
    {
        return false;
    }
    position.x += 1;

    if (getEtatEffetBanane() && position.x < 4)
    {
        position.x += 1;
    }

    return true;
}

bool Joueur::Left()
{
    if (position.x <= 0) 
    {
        return false;
    }
    position.x -= 1;

    if (getEtatEffetBanane() && position.x > 0)
    {
        position.x -= 1;
    }
    
    return true;
}

Coordonnee Joueur::getPosition() const
{

    return position;
}

void Joueur::setPosition(const Coordonnee &pos)
{

    position = pos;
}
