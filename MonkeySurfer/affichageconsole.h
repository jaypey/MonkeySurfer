#ifndef AFFICHAGECONSOLE_H
#define AFFICHAGECONSOLE_H

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include "affichage.h"
#include "cmdcolor.h"
#include "skin.h"

#define NB_COLS 61
#define NB_LIGNES 25

#define NB_LIANES 5
#define ECART_LIANES 10

#define ECART_COL_SKINS 17
#define ECART_RANGEE_SKINS 6

#define FPS 30 // Images par seconde (Frames per second)

struct CharInfo {
    char c;
    CMDColor color;
};

class AffichageConsole : public Affichage
{
public:
    AffichageConsole(Jeu *j, Menu *m);
    ~AffichageConsole();

    // Affichage à la console (cout)
    void afficherJeu();
    void afficherMenu();
private:
    // Affichage menu;
    void afficherMenuPrincipal();
    void afficherMenuSkin();
    void afficherAide();
    void afficherLoading();

    // Fonctions d'initialisation du jeu
    void initialiserLianes();

    // Mise à jour de la matrice de char
    void afficherArrierePlan();
    void afficherLianes();
    void afficherJoueur();
    void afficherItems();
    void afficherIU();
    void afficherGameOver();
    void afficherPause();
    void afficherContour(); // Non herite
    void afficherTexte(std::string s, int x, int y, CMDColor color = CMD_WHITE, bool selected = false); // Non herite
    void afficherFichier(std::string nom, int x, int y, CMDColor color = CMD_WHITE); // Non herite

    // Mise à jour de la déco (feuilles)
    void updateDeco();

    // Fonctions "helper" pour l'affichage à la console
    void printMatriceChar();
    CharInfo getCharEclat();

    // Lié au FPS
    bool peutAfficherProchaineImage(); // Attendre que l'image precedente aie finie de s'afficher, vitesse d'affichage limitee par le FPS
    void attendreProchaineImage(); // Attend que "peutAfficherProchaineImage" soit true

private:
    // Affichage
    CharInfo _img[NB_COLS][NB_LIGNES]; // Informations de l'image à imprimer a la console
    std::string _output; // Image a imprimer a la console
    std::chrono::steady_clock::time_point _lastfrm; // Temps ecoule depuis dernier affichage
    std::chrono::steady_clock::time_point _lastupdate; // Temps ecoule depuis derniere update du jeu

    const long long _DURFRM = 1000 / FPS; // Duree d'affichage d'une image avant d'afficher la prochaine, en millisecondes
    RandomGenerator _rand;

    // Lianes
    int _xlianes[NB_LIANES]; // Emplacement colonne des lianes
    Coordonnee _feuilles[NB_LIANES][3]; // Des feuilles accrochées aux lianes pour points bonus esthetique

    // UI
    std::string _score; // Texte pour afficher le score
};

#endif // !AFFICHAGECONSOLE_H
