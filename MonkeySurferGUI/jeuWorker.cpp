#include "jeuWorker.h"
#include <QDebug>

void JeuWorker::doWork() {
	qDebug() << "Work in thread:" << QThread::currentThread();
}
