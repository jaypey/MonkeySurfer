#include "menu.h"
#include "networking.h"
#include <iostream>

Menu::Menu(Joueur *joueur, JsonSerial *jsonserial, Networking *n)
    : _choixMenu(0), _indexSkin(0), _indexSkinPreview(0), _etat(EtatMenu::PRINCIPAL), _joueur(joueur), _jsonserial(jsonserial), _networking(n)
{
    initialiserSkins();
}

Menu::~Menu() {}

void Menu::initialiserSkins()
{
    std::ifstream fichier("data/skins.txt");
    std::string ligne;

    for (int i = 0; i < NB_SKINS; i++)
    {
        std::getline(fichier, ligne, ' ');
        _skins[i].setId(ligne[0]);

        std::getline(fichier, ligne, ' ');
        _skins[i].setFile(ligne.c_str());

        std::getline(fichier, ligne, ' ');
        _skins[i].setPrix(std::stoi(ligne));

        std::getline(fichier, ligne, '\n');
        _skins[i].setDebloque(std::stoi(ligne));
    }
}

void Menu::update()
{
    if (_etat == EtatMenu::MULTIJOUEUR)
    {
        if (_networking->IsGameStarted())
        {
            _etat = EtatMenu::MULTIJOUEURJEU;
        }
        return;
    }

    if (_etat == EtatMenu::PRINCIPAL)
    {
        // MANETTE
        if (_jsonserial->joystickMaintenu(HAUT, true))
            modifierChoixMenu(1);
        if (_jsonserial->joystickMaintenu(BAS, true))
            modifierChoixMenu(-1);

        if (_jsonserial->boutonAppuye(2))
        {
            if (_choixMenu == 0)
            {
                _etat = EtatMenu::CHARGEMENT;
                _timer = std::chrono::steady_clock::now();
            }
            else if (_choixMenu == 1)
            {
                std::cout << "Adresse du serveur: " << std::endl;
                std::cin >> ipAddress;
                _etat = EtatMenu::MULTIJOUEUR;
                _networking->Connect(ipAddress, 7777);
            }
            else if (_choixMenu == 2)
                _etat = EtatMenu::SKINS;
            else if (_choixMenu == 3)
                _etat = EtatMenu::AIDE;
            else if (_choixMenu == 4)
                _etat = EtatMenu::QUITTER;
        }

        // CLAVIER
        if (_kbhit())
        {
            char c = _getch();

            if (c == '1')
            {
                _etat = EtatMenu::CHARGEMENT;
                _timer = std::chrono::steady_clock::now();
            }
            else if (c == '2')
                _etat = EtatMenu::SKINS;
            else if (c == '3')
                _etat = EtatMenu::AIDE;
            else if (c == '4')
                _etat = EtatMenu::QUITTER;
        }
    }
    else if (_etat == EtatMenu::SKINS)
    {
        // MANETTE
        if (_jsonserial->joystickMaintenu(GAUCHE, true))
            modifierSkinPreview(-1);
        if (_jsonserial->joystickMaintenu(HAUT, true))
            modifierSkinPreview(3);
        if (_jsonserial->joystickMaintenu(DROITE, true))
            modifierSkinPreview(1);
        if (_jsonserial->joystickMaintenu(BAS, true))
            modifierSkinPreview(-3);
        if (_jsonserial->boutonAppuye(1))
            _etat = EtatMenu::PRINCIPAL;
        if (_jsonserial->boutonAppuye(2))
            choisirSkin(_indexSkinPreview);

        // CLAVIER
        if (_kbhit())
        {
            char c = _getch();
            if (c == 224)
                c = _getch(); // Les caract�res sp�ciaux �mettent deux char (224 -> code de fl�che)
            if (c == 75)
                modifierSkinPreview(-1); // LEFT
            else if (c == 72)
                modifierSkinPreview(-3); // UP
            else if (c == 77)
                modifierSkinPreview(1); // RIGHT
            else if (c == 80)
                modifierSkinPreview(3); // DOWN
            else if (c == 'q')
                _etat = EtatMenu::PRINCIPAL;
            else if (c == ' ')
                choisirSkin(_indexSkinPreview);
        }
    }
    else if (_etat == EtatMenu::AIDE)
    {
        // MANETTE
        if (_jsonserial->boutonAppuye(1))
            _etat = EtatMenu::PRINCIPAL;

        // CLAVIER
        if (_kbhit())
        {
            char c = _getch();
            if (c == 'q')
                _etat = EtatMenu::PRINCIPAL;
        }
    }
    else if (_etat == EtatMenu::CHARGEMENT)
    {
        auto current = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(current - _timer);
        if (elapsed.count() >= 3)
            _etat = EtatMenu::JEU;
    }
}

void Menu::modifierChoixMenu(int val)
{
    _choixMenu = (_choixMenu + val) % 4;
    if (_choixMenu < 0)
        _choixMenu = 3;
}

void Menu::modifierSkinPreview(int val)
{
    _indexSkinPreview = (_indexSkinPreview + val) % NB_SKINS;
    if (_indexSkinPreview < 0)
        _indexSkinPreview += NB_SKINS;
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

void Menu::setEtat(EtatMenu e)
{
    _etat = e;
}

Menu::EtatMenu Menu::getEtat()
{
    return _etat;
}

int Menu::getChoixMenu()
{
    return _choixMenu;
}

int Menu::getIndexSkin()
{
    return _indexSkin;
}

int Menu::getIndexSkinPreview()
{
    return _indexSkinPreview;
}

void Menu::choisirSkin(int index)
{
    if (_skins[index].isDebloque())
    {
        _indexSkin = index;
    }
    else if (_skins[index].getPrix() <= _joueur->getPiece())
    {
        _joueur->addPiece(-_skins[index].getPrix());
        _indexSkin = index;
        _skins[index].setDebloque(true);
    }
}

Skin Menu::getSkin(int index)
{
    return _skins[index];
}
