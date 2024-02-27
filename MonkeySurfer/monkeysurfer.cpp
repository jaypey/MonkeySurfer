#include "affichageconsole.h"
#include <conio.h>

#include "jsonserial.h"

int main()
{
    JsonSerial js;
    char c;

    js.openSerialPort("COM5");
    js.readSerial();
    while (!(_kbhit() && (c = _getch()) == 'q')) {
        js.readSerial();
        js.printData();
    }

    //Jeu j;
    //Menu m;
    //AffichageConsole a(&j, &m);

    //while (m.getEtat() != Menu::EtatMenu::QUITTER) {
    //    if (m.getEtat() == Menu::EtatMenu::JEU) {
    //        a.afficherJeu();
    //        if (_kbhit() && _getch() == 'q') {
    //            m.setEtat(Menu::EtatMenu::PRINCIPAL);
    //            continue;
    //        }
    //    }
    //    else {
    //        m.update();
    //        a.afficherMenu();
    //    }
    //}
}
