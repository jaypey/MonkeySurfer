#include "joueur.h"
#include "jeu.h"
#include "menu.h"
#include "affichageconsole.h"


int main()
{
    Joueur* p1 = new Joueur();
    Jeu j(p1);
    Menu m;
    AffichageConsole a(&j, &m);

    while (m.getEtat() != Menu::EtatMenu::QUITTER) {
        if (m.getEtat() == Menu::EtatMenu::JEU) {
            j.debuterPartie();
            a.afficherJeu();
            if (_kbhit() && _getch() == 'q') {
                m.setEtat(Menu::EtatMenu::PRINCIPAL);
                delete p1;
                p1 = new Joueur();
                j.restartJeu(p1);
                continue;
            }
        }
        else {
            m.update();
            a.afficherMenu();
        }
    }
