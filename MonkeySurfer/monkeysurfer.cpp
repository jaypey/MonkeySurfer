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
        unsigned char c;
        while ((c = _getch()) != '3') {
            if (c == '1') {
                while (true) a.afficherJeu();
            }
            else if (c == '2') {
                a.afficherMenuSkin();
                while ((c = _getch()) != 'q') {
                    if (c == 224) c = _getch(); // Les caractères spéciaux émettent deux char (224, code de flèche)
                    if (c == 75)        a.modifierSkin(-1); // LEFT
                    else if (c == 72)   a.modifierSkin(-3);  // UP
                    else if (c == 77)   a.modifierSkin(1);  // RIGHT
                    else if (c == 80)   a.modifierSkin(3); // DOWN
                    a.afficherMenuSkin();
                }
            }
            a.afficherMenu();
        }
    }
}
