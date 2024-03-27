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

    Joueur* p1 = new Joueur();
    Jeu j(p1, &js);
    Networking n;
    Menu m(&n);
    AffichageConsole a(&j, &m);

    while (m.getEtat() != Menu::EtatMenu::QUITTER) {
        // Communication avec l'arduino
        js.sendJson();
        js.recvJson();

        // Gestion jeu
        if (m.getEtat() == Menu::EtatMenu::JEU || m.getEtat() == Menu::EtatMenu::MULTIJOUEURJEU) {
            if (m.getEtat() == Menu::EtatMenu::MULTIJOUEURJEU)
            {
                j.debuterPartieMultijoueur(&n);
            }
            else {
                j.debuterPartie();
            }
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

    exit(0);
}