#include <QApplication>

#include "affichagegui.h"
#include "jeu.h"
#include "joueur.h"
#include "jsonSerial.h"
#include "menu.h"
#include "networking.h"
#include <mainwindow.h>
#include <QFontDatabase>

int main(int argv, char** args)
{
    QApplication app(argv, args);

    //Setup fonts
    QFontDatabase::addApplicationFont(QString(":/fonts/JungleFeverNF.otf"));

    QFont defaultFont;
    defaultFont.setFamily("Jungle Fever NF");
    defaultFont.setPointSize(20);
    app.setFont(defaultFont);

    JsonSerial jsonSerial;
    jsonSerial.openSerialPort("COM3");

    Joueur joueur;
    Jeu jeu(&joueur, &jsonSerial);
    Networking networking;
    Menu menu(&joueur, &jsonSerial, &networking);

    AffichageGUI affichage(&jeu, &menu);

    MonkeySurferMainWindow mainwindow(&affichage, &menu);

    QObject::connect(&affichage, &AffichageGUI::retourMenu, &mainwindow, &MonkeySurferMainWindow::handleRetourMenu);

    mainwindow.showFullScreen();

    app.exec();
}