#include "jeuWorker.h"

#include "joueur.h"
#include "jeu.h"
#include "menu.h"
#include "jsonserial.h"
#include "networking.h"
#include <QDebug>

JeuWorker::JeuWorker(JsonSerial* js, Jeu* j) : _jsonSerial(js), _jeu(j) {}

void JeuWorker::doWork() {
    qDebug() << "Work in thread:" << QThread::currentThread();

    while (true) {
        _jsonSerial->sendJson();
        _jsonSerial->recvJson();

        _jeu->debuterPartie();
        qDebug() << _jeu->getPointageJoueur();
    }
}
