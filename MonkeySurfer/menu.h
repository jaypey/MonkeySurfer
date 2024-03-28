#ifndef MENU_H
#define MENU_H

#include <chrono>
#include <conio.h>
#include <fstream>
#include "joueur.h"
#include "jsonserial.h"
#include "skin.h"

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
    Menu(Joueur* joueur, JsonSerial* jsonserial);
    ~Menu();

    void initialiserSkins();

    void update();
    void modifierChoixMenu(int val);
    void modifierSkinPreview(int val);
    void setEtat(EtatMenu e);
    EtatMenu getEtat();
    int getChoixMenu();
    int getIndexSkin();
    int getIndexSkinPreview();
    void choisirSkin(int index);
    void updateUnlocksFile();
    Skin getSkin(int index);
private:
    int _choixMenu;
    int _indexSkin;
    int _indexSkinPreview;
    EtatMenu _etat;
    std::chrono::steady_clock::time_point _timer;
    Joueur* _joueur;
    JsonSerial* _jsonserial;
    Skin _skins[NB_SKINS];
};

#endif // MENU_H!
