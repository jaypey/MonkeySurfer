#include "jeuWorker.h"

#include "joueur.h"
#include "jeu.h"
#include "menu.h"
#include "jsonserial.h"
#include "networking.h"

#include <QDebug>
void JeuWorker::doWork() {
    JsonSerial js;
    js.openSerialPort("COM4");

    Joueur p1;
    Networking n;
    Jeu j(&p1, &js);

	qDebug() << "Work in thread:" << QThread::currentThread();

    while (true) {
        js.sendJson();
        js.recvJson();

        j.debuterPartie();
        qDebug() << j.getPointageJoueur();
    }
}
