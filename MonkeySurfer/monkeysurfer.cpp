#include "affichageconsole.h"
#include <conio.h>

int main()
{
    // test affichage, remplacer condition par false pour desactiver test
    if (true)
    {
        Jeu j;
        AffichageConsole a(&j);
        a.afficherMenu();
        char c;
        while ((c = _getch()) != '3') {
            if (c == '1') {
                while (true) a.afficherJeu();
            }
            else if (c == '2') {
                // TODO - menu skins
            }
        }
    }
}
