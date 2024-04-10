#ifndef SKINSHOP_H
#define SKINSHOP_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QVBoxLayout> // Include for layout management
#include "skin.h"

class SkinShop : public QWidget
{
    Q_OBJECT
public:
    explicit SkinShop(QWidget* parent = nullptr);

private:
};

#endif // SKINSHOP_H