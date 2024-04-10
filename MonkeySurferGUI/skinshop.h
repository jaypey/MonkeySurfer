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
#include <QPushButton>
#include <QPixmap>
#include "skin.h"

class SkinShop : public QWidget
{
    
public:
    explicit SkinShop();
    ~SkinShop();
    int getSelectedSkin();


private:
   
    QVBoxLayout* layout;
    QGraphicsView* view;
    QGraphicsScene* scene;
    std::vector<Skin> skins;
    int m_selectedSkinIndex;
    QGraphicsPixmapItem* skin1;
    QGraphicsPixmapItem* skin2;
    QGraphicsPixmapItem* skin3;
    QGraphicsPixmapItem* skin4;
    QGraphicsPixmapItem* skin5;
    QGraphicsPixmapItem* skin6;
    QGraphicsPixmapItem* skin7;
    QGraphicsPixmapItem* skin8;
    QGraphicsPixmapItem* skin9;

    void setupUI();
    void loadSkins();
    void displaySkins();
    void createSkinItem(const Skin& skin, int position);
};
#endif // SKINSHOP_H