#ifndef AFFICHAGECONSOLE_H
#define AFFICHAGECONSOLE_H

#include <iostream>
#include <chrono>
#include "affichage.h"

#define NB_COLS 41
#define NB_LIGNES 20
#define NB_LIANES 5
#define ECART_LIANES 6
#define FPS 30 // Images par seconde (Frames per second)

class AffichageConsole : public Affichage
{
public:
    AffichageConsole(Jeu *);
    ~AffichageConsole();

    void afficher();
    void afficherArrierePlan();
    void afficherLianes();
    void afficherJoueur();
    void afficherItems();
    void afficherObstacles();
    void afficherIU();

    bool peutAfficherProchaineImage(); // Attendre que l'image pr�c�dente aie finie de s'afficher, vitesse d'affichage limit�e par le FPS
private:
    char _img[NB_COLS][NB_LIGNES]; // Informations de l'image � imprimer � la console
    std::string _output; // Image � imprimer � la console
    std::chrono::steady_clock::time_point _lastfrm; // Temps �coul� depuis dernier affichage
    int _xlianes[NB_LIANES]; // Emplacement colonne des lianes

    const long long _DURFRM = 1000 / FPS; // Dur�e d'affichage d'une image avant d'afficher la prochaine, en millisecondes
};

#endif // !AFFICHAGECONSOLE_H
