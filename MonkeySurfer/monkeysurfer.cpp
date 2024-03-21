#include "joueur.h"
#include "jeu.h"
#include "menu.h"
#include "affichageconsole.h"
#include "jsonserial.h"

int main()
{
    JsonSerial js;
    js.openSerialPort("COM4");

    Joueur* p1 = new Joueur();
    Jeu j(p1, &js);
    Menu m;
    AffichageConsole a(&j, &m);

    while (m.getEtat() != Menu::EtatMenu::QUITTER) {
        // Communication avec l'arduino
        js.sendJson();
        js.recvJson();

        // Gestion jeu
        if (m.getEtat() == Menu::EtatMenu::JEU) {
            j.debuterPartie();
            a.afficherJeu();
            if (j.isQuitting()) {
                m.setEtat(Menu::EtatMenu::PRINCIPAL);
                delete p1;
                p1 = new Joueur();
                j.restartJeu(p1);
            }

            std::cout << "Etat accelerometre: " << js.accShake();
        }
        else {
            m.update();
            a.afficherMenu();
        }
    }

    exit(0);
}