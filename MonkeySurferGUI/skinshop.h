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
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include "skin.h"

class SkinShop : public QWidget
{
    
public:
    explicit SkinShop();

   
    int getSelectedSkin();


private:
    int m_selectedSkinIndex;
    void updateskinselection();
    void loadSkins();
    void displaySkinPreview();
    
    
};
#endif // SKINSHOP_H