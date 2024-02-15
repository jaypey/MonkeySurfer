#include "Joueur.h"
#include <algorithm>


Joueur:: Joueur(){
    score = 0;
    nbPieces = 0;
    nbObjets - 0;
}

Joueur::~Joueur(){
}

int Joueur::getPiece(){
    return nbPieces;
}

int Joueur::getScore(){
    return score;
}

void Joueur::ramasserPiece(){
    nbPieces += 1;
}

void Joueur::conteurPointage(){
    
}