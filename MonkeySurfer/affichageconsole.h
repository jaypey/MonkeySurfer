#ifndef AFFICHAGECONSOLE_H
#define AFFICHAGECONSOLE_H

#include <chrono>
#include <iostream>
#include <string>
#include "affichage.h"

#include "skin.h" // TODO - enlever ce include quand d'autres fichiers l'auront déjà include

#define NB_COLS 61
#define NB_LIGNES 25

#define NB_LIANES 5
#define ECART_LIANES 6
#define FPS 60 // Images par seconde (Frames per second)

// Ceci est soit temporaire, soit ce sera bougé dans un autre fichier
struct Coord {
    int x;
    int y;
};

class AffichageConsole : public Affichage
{
public:
    AffichageConsole(Jeu *);
    ~AffichageConsole();

    // Affichage à la console (cout)
    void afficherJeu();
    void afficherMenu();

private:
    // Fonctions d'initialisation du jeu
    void initialiserLianes();

    // Mise à jour de la matrice de char
    void afficherArrierePlan();
    void afficherLianes();
    void afficherJoueur();
    void afficherItems();
    void afficherObstacles();
    void afficherIU();
    void afficherContour(); // Non hérité
    void afficherTexte(const std::string& s, int x, int y); // Non hérité

    // Fonctions "helper" pour l'affichage à la console
    void printMatriceChar();

    // Lié au FPS
    bool peutAfficherProchaineImage(); // Attendre que l'image précédente aie finie de s'afficher, vitesse d'affichage limitée par le FPS

private:
    // Affichage
    char _img[NB_COLS][NB_LIGNES]; // Informations de l'image à imprimer à la console
    std::string _output; // Image à imprimer à la console
    std::chrono::steady_clock::time_point _lastfrm; // Temps écoulé depuis dernier affichage

    const long long _DURFRM = 1000 / FPS; // Durée d'affichage d'une image avant d'afficher la prochaine, en millisecondes

    // Lianes
    int _xlianes[NB_LIANES]; // Emplacement colonne des lianes
    Coord _feuilles[NB_LIANES][3]; // Des feuilles accrochées aux lianes pour points bonus esthétique

    // UI
    std::string _score; // Texte pour afficher le score
};

#endif // !AFFICHAGECONSOLE_H
