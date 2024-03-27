#ifndef MENU_H
#define MENU_H

#include <chrono>
#include <conio.h>
#include "networking.h"

#define NB_SKINS 9

class Menu {
public:
    enum class EtatMenu {
        PRINCIPAL,
        CHARGEMENT,
        JEU,
        MULTIJOUEUR,
        MULTIJOUEURJEU,
        SKINS,
        AIDE,
        QUITTER
    };
public:
    Menu(Networking* n);
    ~Menu();

    void update();
    void modifierSkin(int val);
    void getNbMultijoueurReady();
    void getNbMultijoueurConnectes();
    void setEtat(EtatMenu e);
    EtatMenu getEtat();
    int getIndexSkin();
private:
    int _indexSkin;
    EtatMenu _etat;
    Networking* _networking;
    std::chrono::steady_clock::time_point _timer;
};

#endif // MENU_H!
