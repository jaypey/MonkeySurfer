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

   
    int getSelectedSkin();


private:
   
    QVBoxLayout* layout;
    QGraphicsView* view;
    QGraphicsScene* scene;
    QPushButton* exitButton;
    std::vector<Skin> skins;
    int m_selectedSkinIndex;

    void setupUI();
    void loadSkins();
    void displaySkins();
    void createSkinItem(const Skin& skin, int position);
};
#endif // SKINSHOP_H