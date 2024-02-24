#include "Joueur.h"



Joueur::Joueur(){
    score = 0;
    nbPieces = 0;
    nbObjets - 0;
    inventaire[0] = -1; //Tableau objets initialement vide
    inventaire[1] = -1;
    lastUpdate = std::chrono::steady_clock::now(); //moment dernier update pour score
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
    score +=10 // A revoir si on conserve
}

void Joueur::compteurPointage(){
    

}

void Joueur::ajouterInventaire(int idObj){
    if (inventaire[0] == -1) {
        inventaire[0] = idObj;
    }
    else if (inventaire[1] == -1) {
        inventaire[1] == idObj;
    }
    //Si inventaire plein, objet nest pas recupere, on pourra discuter de ce scenario en equipe
}



void Joueur::echangerInventaire() {
    if (inventaire[0] != -1 && inventaire[1] != -1) {
        std::swap(inventaire[0], inventaire[1]);
    }
}

double Joueur::position() {

}

void Joueur::useObjet(int idObj) {
    //Sais pas trop comment renvoyer l'id objet, ca va ou dans le code apres?
    if (inventaire[0] != -1) { //Si inventaire pas vide
        if (inventaire[1] != -1) { //si 2e objet, reviens a la pos 0
            inventaire[0] = inventaire[1];
            inventaire[1] = -1;
        }
        else { //si juste un obj, utilise
            inventaire[0] == -1; //vide la position 0
        }
    }
}