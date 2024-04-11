#ifndef ITEMGUI_H
#define ITEMGUI_H

#include <QGraphicsRectItem>
#include "elementjeu.h"

struct ItemGui {
	ElementJeu* item;
	QGraphicsPixmapItem* gui;
};

#endif // !ITEMGUI_H
