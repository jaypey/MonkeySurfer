#include "joueur.h"
#include "jeu.h"
#include "menu.h"
#include "affichageconsole.h"
#include "jsonserial.h"
#include "networking.h"

int main()
{
    JsonSerial js;
    js.openSerialPort("COM4");

    Joueur p1;
    Networking n;
    Jeu j(&p1, &js);
    Menu m(&p1, &js, &n);

    AffichageConsole a(&j, &m);

    while (m.getEtat() != Menu::EtatMenu::QUITTER)
    {
        if (m.getEtat() == Menu::EtatMenu::MULTIJOUEUR || m.getEtat() == Menu::EtatMenu::MULTIJOUEURJEU)
        {
            n.ReceiveData();
        }
        // Communication avec l'arduino
        js.sendJson();
        js.recvJson();

        // Gestion jeu
        if (m.getEtat() == Menu::EtatMenu::JEU || m.getEtat() == Menu::EtatMenu::MULTIJOUEURJEU)
        {
            if (m.getEtat() == Menu::EtatMenu::MULTIJOUEURJEU)
            {
                j.debuterPartieMultijoueur(&n);
            }
            else
            {
                j.debuterPartie();
            }
            a.afficherJeu();
            if (j.isQuitting())
            {
                m.setEtat(Menu::EtatMenu::PRINCIPAL);
                p1.reset();
                j.restartJeu(&p1);
            }
        }
        else
        {
            m.update();
            a.afficherMenu();
        }
    }

    exit(0);
}