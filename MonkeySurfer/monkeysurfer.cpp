#include "joueur.h"
#include "jeu.h"
#include "menu.h"
#include "affichageconsole.h"
#include "jsonserial.h"

int main()
{
    JsonSerial js;
    js.openSerialPort("COM4");

    auto last = std::chrono::steady_clock::now();

    while (true) {
        js.sendJson();
        js.recvJson();

        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last);
        if (elapsed.count() > 50) {
            std::cout << "Bouton appuye: " << js.boutonAppuye(1) << std::endl;
            last = std::chrono::steady_clock::now();
        }
    }

    //Joueur* p1 = new Joueur();
    //Jeu j(p1);
    //Menu m;
    //AffichageConsole a(&j, &m);

    //while (m.getEtat() != Menu::EtatMenu::QUITTER) {
    //    if (m.getEtat() == Menu::EtatMenu::JEU) {
    //        j.debuterPartie();
    //        a.afficherJeu();
    //        if (_kbhit() && _getch() == 'q') {
    //            m.setEtat(Menu::EtatMenu::PRINCIPAL);
    //            delete p1;
    //            p1 = new Joueur();
    //            j.restartJeu(p1);
    //            continue;
    //        }
    //    }
    //    else {
    //        m.update();
    //        a.afficherMenu();
    //    }
    //}
}