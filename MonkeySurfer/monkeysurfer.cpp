#include "affichageconsole.h"

int main()
{
    // test affichage, remplacer condition par false pour desactiver test
    if (true)
    {
        Jeu j;
        AffichageConsole a(&j);
        a.afficherMenu();
        system("pause & cls");
        while (true)
            a.afficherJeu();
    }
}
