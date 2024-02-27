#include "affichageconsole.h"
#include <conio.h>
#include "joueur.h"
#include "jeu.h"

int main()
{
    Joueur p1;
    Jeu j(&p1);
    Menu m;
    AffichageConsole a(&j, &m);

    while (m.getEtat() != Menu::EtatMenu::QUITTER) {
        if (m.getEtat() == Menu::EtatMenu::JEU) {
            a.afficherJeu();
            if (_kbhit() && _getch() == 'q') {
                m.setEtat(Menu::EtatMenu::PRINCIPAL);
                continue;
            }
        }
        else {
            m.update();
            a.afficherMenu();
        }
    }
}
