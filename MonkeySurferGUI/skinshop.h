#ifndef SKINSHOP_H
#define SKINSHOP_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include "skin.h"

class SkinShop : public QWidget
{
  
public:
    void addScene(QGraphicsScene* scene);
    void setVisible(bool visible);
    int getSelectedSkin();


private:
    int m_selectedSkinIndex;
    void loadSkins();
    void displaySkinPreview();
};

#endif // SKINSHOP_H