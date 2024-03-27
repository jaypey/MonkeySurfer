#include "menu.h"

Menu::Menu(JsonSerial* jsonserial) : _choixMenu(0), _indexSkin(0), _etat(EtatMenu::PRINCIPAL), _jsonserial(jsonserial) {}

Menu::~Menu() {}

void Menu::update() {
    if (_etat == EtatMenu::PRINCIPAL) {
        // MANETTE
        if (_jsonserial->joystickMaintenu(HAUT, true)) modifierChoixMenu(1);
        if (_jsonserial->joystickMaintenu(BAS, true))  modifierChoixMenu(-1);

        if (_jsonserial->boutonAppuye(2)) {
            if (_choixMenu == 0) {
                _etat = EtatMenu::CHARGEMENT;
                _timer = std::chrono::steady_clock::now();
            }
            else if (_choixMenu == 1)  _etat = EtatMenu::SKINS;
            else if (_choixMenu == 2)  _etat = EtatMenu::AIDE;
            else if (_choixMenu == 3)  _etat = EtatMenu::QUITTER;
        }

        // CLAVIER
        if (_kbhit()) {
            char c = _getch();

            if (c == '1') {
                _etat = EtatMenu::CHARGEMENT;
                _timer = std::chrono::steady_clock::now();
            }
            else if (c == '2')  _etat = EtatMenu::SKINS;
            else if (c == '3')  _etat = EtatMenu::AIDE;
            else if (c == '4')  _etat = EtatMenu::QUITTER;
        }
    }
    else if (_etat == EtatMenu::SKINS) {
        // MANETTE
        if (_jsonserial->joystickMaintenu(GAUCHE, true))   modifierSkin(-1);
        if (_jsonserial->joystickMaintenu(HAUT, true))     modifierSkin(3);
        if (_jsonserial->joystickMaintenu(DROITE, true))   modifierSkin(1);
        if (_jsonserial->joystickMaintenu(BAS, true))      modifierSkin(-3);
        if (_jsonserial->boutonAppuye(1)) _etat = EtatMenu::PRINCIPAL;

        // CLAVIER
        if (_kbhit()) {
            char c = _getch();
            if (c == 224) c = _getch(); // Les caractères spéciaux émettent deux char (224 -> code de flèche)
            if (c == 75)        modifierSkin(-1); // LEFT
            else if (c == 72)   modifierSkin(-3); // UP
            else if (c == 77)   modifierSkin(1);  // RIGHT
            else if (c == 80)   modifierSkin(3);  // DOWN
            else if (c == 'q')  _etat = EtatMenu::PRINCIPAL;
        }
    }
    else if (_etat == EtatMenu::AIDE) {
        // MANETTE
        if (_jsonserial->boutonAppuye(1)) _etat = EtatMenu::PRINCIPAL;

        // CLAVIER
        if (_kbhit()) {
            char c = _getch();
            if (c == 'q')  _etat = EtatMenu::PRINCIPAL;
        }
    }
    else if (_etat == EtatMenu::CHARGEMENT) {
        auto current = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(current - _timer);
        if (elapsed.count() >= 3) _etat = EtatMenu::JEU;
    }
}

void Menu::modifierChoixMenu(int val) {
    _choixMenu = (_choixMenu + val) % 4;
    if (_choixMenu < 0) _choixMenu = 3;
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

int Menu::getChoixMenu() {
    return _choixMenu;
}

int Menu::getIndexSkin() {
    return _indexSkin;
}
