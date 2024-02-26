#ifndef MENU_H
#define MENU_H

#include <chrono>
#include <conio.h>

#define NB_SKINS 9

class Menu {
public:
    enum class EtatMenu {
        PRINCIPAL,
        CHARGEMENT,
        JEU,
        SKINS,
        AIDE,
        QUITTER
    };
public:
    Menu();
    ~Menu();

    void update();
    void modifierSkin(int val);
    void setEtat(EtatMenu e);
    EtatMenu getEtat();
    int getIndexSkin();
private:
    int _indexSkin;
    EtatMenu _etat;
    std::chrono::steady_clock::time_point _timer;
};

#endif // MENU_H!
