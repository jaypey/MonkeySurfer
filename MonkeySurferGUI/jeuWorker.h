#ifndef JEUWORKER_H
#define JEUWORKER_H

#include <QObject>
#include <QThread>
#include "jeu.h"
#include "jsonSerial.h"

class JeuWorker : public QObject {
    Q_OBJECT
public:
    JeuWorker(JsonSerial* js, Jeu* j);
public slots:
    void doWork();
private:
    JsonSerial* _jsonSerial;
    Jeu* _jeu;
};

#endif // !JEUWORKER_H
