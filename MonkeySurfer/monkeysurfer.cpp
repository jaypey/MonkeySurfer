#include "affichageconsole.h"

int main()
{
    // test affichage, remplacer condition par false pour desactiver test
    if (true)
    {
        Jeu j;
        AffichageConsole a(&j);
        while (true)
            a.afficherJeu();
    }
}
