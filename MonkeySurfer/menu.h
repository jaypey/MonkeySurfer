#ifndef MENU_H
#define MENU_H

#include <chrono>
#include <conio.h>
#include "jsonserial.h"

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
    Menu(JsonSerial* jsonserial);
    ~Menu();

    void update();
    void modifierChoixMenu(int val);
    void modifierSkin(int val);
    void setEtat(EtatMenu e);
    EtatMenu getEtat();
    int getChoixMenu();
    int getIndexSkin();
private:
    int _choixMenu;
    int _indexSkin;
    EtatMenu _etat;
    std::chrono::steady_clock::time_point _timer;
    JsonSerial* _jsonserial;
};

#endif // MENU_H!
