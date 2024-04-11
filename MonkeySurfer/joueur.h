#ifndef JOUEUR_H
#define JOUEUR_H

#include <chrono>
#include <fstream>
#include <string>
#include "coordonnee.h"
#include "elementjeu.h"
#include "skin.h"

#ifdef USE_QT
#include <QObject>
#endif

struct charInventaire {
    char item1;
    char item2;
};
class Serpent;
class Collectible;
class Joueur
#ifdef USE_QT
    : public QObject
#endif
{
#ifdef USE_QT
    Q_OBJECT
#endif
public:
    Joueur();
    ~Joueur();

    void reset();

    int getPiece();
    void addPiece(int n);
    int getScore();
    void ramasserPiece();
    void loadPieces();
    void compteurPointage();
    int getNbItem();
    bool ajouterInventaire(Collectible *powerUp);
    charInventaire getCharInventaire();
    void setCharInventaire(charInventaire c);

    bool echangerInventaire();
    void useObjet();
    void enleverObjet();
    
    void switchEtatBouclier();
    void setEtatBouclier(bool etat);
    bool getEtatBouclier();

    void switchEtatEffetBanane();
    void setEtatEffetBanane(bool etat);
    bool getEtatEffetBanane();

    void immobiliser(bool etat);
    bool isFree();

    bool getVie();
    void isDead();

    int getNbBoost();
    void setNbBoost(int nb);

    Serpent* getSerpent();
    void setSerpent(Serpent* serpent);

    Coordonnee getPosition() const;
    void setPosition(const Coordonnee &pos);
    bool up();
    bool down();
    bool Right();
    bool Left();
#ifdef USE_QT
signals:
    void mouvementSinge();
#endif
private:
    Coordonnee position;
    bool bouclierActif;
    bool effetBanane;
    bool immobilise;
    bool enVie;
    int nbBoost;
    Serpent* _serpent;

    int nbPieces;
    int score;
    int nbObjets;
    Collectible* inventaire[2];
    charInventaire charInv;
    std::chrono::steady_clock::time_point lastUpdate;
};

#include "collectible.h"

#endif // !JOUEUR_H
