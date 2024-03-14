#include "Joueur.h"

Joueur::Joueur()
{
    score = 0;
    nbPieces = 0;
    nbObjets = 0;
    bouclierActif = false;
    effetBanane = false;
    immobilise = false;

    inventaire[0] = -1; // Tableau objets initialement vide
    inventaire[1] = -1;

    position.x = 2;
    position.y = 15;
    lastUpdate = std::chrono::steady_clock::now(); // moment dernier update pour score, initialiser
}

Joueur::~Joueur()
{
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

bool Joueur::ajouterInventaire(int idObj)
{

    if (inventaire[0] == -1)
    {
        inventaire[0] = idObj; // objet ajoute a la pos 0 de l'inventaire
        return true;
    }
    else if (inventaire[1] == -1)
    {
        inventaire[1] = idObj; // Objet ajoute a la pos 1 de l'inventaire
        return true;
    }
    return false;
    // Si inventaire plein, objet nest pas recupere, on pourra discuter de ce scenario en equipe
}

bool Joueur::echangerInventaire()
{

    if (inventaire[0] != -1 && inventaire[1] != -1)
    {
        std::swap(inventaire[0], inventaire[1]);

        return true;
    }

    return false;
}

int Joueur::useObjet(int idObj)
{

    int usedObj = inventaire[0];
    inventaire[0] = inventaire[1];
    inventaire[1] = -1;

    return usedObj; // retourne lobjet a la position 0, qui est lobjet utilise
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
