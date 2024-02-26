#include "menu.h"

Menu::Menu() : _indexSkin(0), _etat(EtatMenu::PRINCIPAL) {}

Menu::~Menu() {}

void Menu::update() {
    if (!_kbhit())
        return;

    char c = _getch();
    
    if (_etat == EtatMenu::PRINCIPAL) {
        if (c == '1')       _etat = EtatMenu::JEU;
        else if (c == '2')  _etat = EtatMenu::SKINS;
        else if (c == '3')  _etat = EtatMenu::AIDE;
        else if (c == '4')  _etat = EtatMenu::QUITTER;
    }
    else if (_etat == EtatMenu::SKINS) {
        if (c == 224) c = _getch(); // Les caract�res sp�ciaux �mettent deux char (224 -> code de fl�che)
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

void Menu::setEtat(EtatMenu e) {
    _etat = e;
}

Menu::EtatMenu Menu::getEtat() {
    return _etat;
}

int Menu::getIndexSkin() {
    return _indexSkin;
}
