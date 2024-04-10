#ifndef DUSTPUFF_H
#define DUSTPUFF_H

#include <chrono>
#include <QGraphicsPixmapItem>

struct DustPuff {
	QGraphicsPixmapItem* pixmap;
	std::chrono::steady_clock::time_point spawnTime;
};

#endif // !DÛSTPUFF_H
