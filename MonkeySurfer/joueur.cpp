#include "Joueur.h"

Joueur::Joueur()
{
    nbPieces = 0;
    reset();
}

Joueur::~Joueur()
{
    // delete inventaire[0];
   // delete inventaire[1];
}

void Joueur::reset() {
    score = 0;
    nbObjets = 0;
    nbBoost = 0;
    bouclierActif = false;
    effetBanane = false;
    immobilise = false;
    enVie = true;

    _serpent = nullptr;
    charInv.item1 = ' ';
    charInv.item2 = ' ';
    inventaire[0] = nullptr;
    inventaire[1] = nullptr;
    position.x = 2;
    position.y = 15;
    lastUpdate = std::chrono::steady_clock::now(); // moment dernier update pour score, initialiser
}

int Joueur::getPiece()
{
    return nbPieces;
}

void Joueur::addPiece(int n) {
    nbPieces += n;
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
        score += 10; // 10 points par tick
        lastUpdate = maintenant;
    }
}

int Joueur::getNbItem()
{
    return nbObjets;
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

charInventaire Joueur::getCharInventaire()
{
    return charInv;
}

void Joueur::setCharInventaire(charInventaire c)
{
    charInv = c;
}

bool Joueur::echangerInventaire()
{
    
    if (nbObjets == 2)
    {
        std::swap(inventaire[0], inventaire[1]);
        char temp = charInv.item1;
        charInv.item1 = charInv.item2;
        charInv.item2 = temp;
        return true;
    }

    return false;
}

void Joueur::useObjet()
{
    if (nbObjets > 0)
    {
        inventaire[0]->appliquerEffet(*this);
        enleverObjet();
    }
    
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

bool Joueur::isFree()
{
    return !immobilise;
}

bool Joueur::getVie()
{
    return enVie;
}

void Joueur::isDead()
{
    enVie = false;
}

int Joueur::getNbBoost()
{
    return nbBoost;
}

void Joueur::setNbBoost(int nb)
{
    nbBoost = nb;
}

Serpent* Joueur::getSerpent()
{
    return _serpent;
}

void Joueur::setSerpent(Serpent* serpent)
{
    _serpent = serpent;
}

bool Joueur::down()
{
    if (!(position.y > 21))
    {
        position.y += 1;
        if (getEtatEffetBanane())
        {
            position.y += 1;
            nbBoost--;
        }
        return true;
    }

    if (nbBoost <= 0)
    {
        setEtatEffetBanane(false);
    }

    return false;
}

bool Joueur::up()
{
    if (!(position.y < 0))
    {
        position.y -= 1;
        if (getEtatEffetBanane())
        {
            position.y -= 1;
            nbBoost--;
        }
        return true;
    }

    if (nbBoost <= 0)
    {
        setEtatEffetBanane(false);
    }

    return false;
}

bool Joueur::Right()
{
    if (position.x >= 4)
    {
        return false;
    }
    position.x += 1;

    if (getEtatEffetBanane())
    {
        position.x += 1;
        nbBoost--;
    }

    if (nbBoost <= 0)
    {
        setEtatEffetBanane(false);
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

    if (getEtatEffetBanane())
    {
        position.x -= 1;
        nbBoost--;
    }

    if (nbBoost <= 0)
    {
        setEtatEffetBanane(false);
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
