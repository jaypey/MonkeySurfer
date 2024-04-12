#ifndef MENU_H
#define MENU_H

#include <chrono>
#include <conio.h>
#include "networking.h"
#include <fstream>
#include "joueur.h"
#include "jsonserial.h"
#include "skin.h"


#define NB_SKINS 9

class Menu
{
public:
    enum class EtatMenu
    {
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
    Menu(Joueur *joueur, JsonSerial *jsonserial, Networking *n);
    ~Menu();

    void initialiserSkins();

    void update();
    void updateMultijoueur();
    int getNbMultijoueurReady();
    int getNbMultijoueurConnectes();
    bool isPlayerReady();
    void updateEtatReady();
    void modifierChoixMenu(int val);
    void modifierSkinPreview(int val);
    void setEtat(EtatMenu e);
    EtatMenu getEtat();
    int getChoixMenu();
    int getIndexSkin();
    JsonSerial* getJsonSerial();
    void connectNetwork(std::string ipAddress);
    int getIndexSkinPreview();
    void choisirSkin(int index);
    void updateSkinDataFile();
    Skin getSkin(int index);
    Networking* getNetworking();
    Skin* getSkins() { return _skins; }

private:
    int _choixMenu;
    int _indexSkin;
    int _indexSkinPreview;
    EtatMenu _etat;
    Networking *_networking;
    std::chrono::steady_clock::time_point _timer;
    Joueur *_joueur;
    JsonSerial *_jsonserial;
    QThread* thread;
    Skin _skins[NB_SKINS];
};

#endif // MENU_H!
