#include <QApplication>

#include "affichagegui.h"
#include "jeu.h"
#include "joueur.h"
#include "jsonSerial.h"
#include "menu.h"
#include "networking.h"

int main(int argv, char** args)
{
    QApplication app(argv, args);

    JsonSerial jsonSerial;
    jsonSerial.openSerialPort("COM4");

    Joueur joueur;
    Jeu jeu(&joueur, &jsonSerial);
    Networking networking;
    Menu menu(&joueur, &jsonSerial, &networking);

    AffichageGUI affichage(&jeu, &menu);

    affichage.showFullScreen();
    app.exec();
}
