#include "affichageconsole.h"
#include <conio.h>

int main()
{
    // test affichage, remplacer condition par false pour desactiver test
    if (true)
    {
        Jeu j;
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
}
