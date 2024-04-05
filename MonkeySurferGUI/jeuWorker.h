#ifndef JEUWORKER_H
#define JEUWORKER_H

#include <QObject>
#include <QThread>

class JeuWorker : public QObject {
	Q_OBJECT
public slots:
	void doWork();
};

#endif // JEUWORKER_H!
