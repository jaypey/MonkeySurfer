#include "menu.h"
#include "networking.h"
#include <iostream>


Menu::Menu(Networking* n)
{
    _indexSkin = 0;
    _etat = EtatMenu::PRINCIPAL;
    _networking = n;
}

Menu::~Menu() {}

void Menu::update() {
    if (!_kbhit() || _etat == EtatMenu::MULTIJOUEUR)
        return;

    char c = _getch();
    std::string ipAddress;
    
    if (_etat == EtatMenu::PRINCIPAL) {
        if (c == '1')       _etat = EtatMenu::JEU;
        if (c == '2') {
            std::cout << "Adresse du serveur: " << std::endl;
            std::cin >> ipAddress;
            _etat = EtatMenu::MULTIJOUEUR;
            _networking->Connect(ipAddress, 7777);
        }
        else if (c == '3')  _etat = EtatMenu::SKINS;
        else if (c == '4')  _etat = EtatMenu::AIDE;
        else if (c == '5')  _etat = EtatMenu::QUITTER;
    }
    else if (_etat == EtatMenu::SKINS) {
        if (c == 224) c = _getch(); // Les caractères spéciaux émettent deux char (224 -> code de flèche)
        if (c == 75)        modifierSkin(-1); // LEFT
        else if (c == 72)   modifierSkin(-3); // UP
        else if (c == 77)   modifierSkin(1);  // RIGHT
        else if (c == 80)   modifierSkin(3);  // DOWN
        else if (c == 'q')  _etat = EtatMenu::PRINCIPAL;
    }
    else if (_etat == EtatMenu::AIDE) {
        if (c == 'q')  _etat = EtatMenu::PRINCIPAL;
    }
    else if (_etat == EtatMenu::CHARGEMENT) {
        auto current = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(current - _timer);
        if (elapsed.count() >= 3) _etat = EtatMenu::JEU;
    }
}

void Menu::modifierSkin(int val) {
    _indexSkin = (_indexSkin + val) % NB_SKINS;
    if (_indexSkin < 0) _indexSkin += NB_SKINS;
}

int Menu::getNbMultijoueurReady()
{
    return _networking->GetReadyPlayerCount();
}

int Menu::getNbMultijoueurConnectes()
{
    return _networking->GetJoueurCount();
}

bool Menu::isPlayerReady()
{
    return _networking->IsPlayerReady();
}

void Menu::updateEtatReady()
{
    _networking->SendLocalReady();
}

void Menu::setEtat(EtatMenu e) {
    _etat = e;
}

Menu::EtatMenu Menu::getEtat() {
    return _etat;
}

int Menu::getIndexSkin() {
    return _indexSkin;
}
