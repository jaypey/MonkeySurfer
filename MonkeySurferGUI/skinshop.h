#ifndef SKINSHOP_H
#define SKINSHOP_H


#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsProxyWidget>
#include <QVector>
#include "joueur.h"


class SkinShop : public QWidget
{
    Q_OBJECT
    
public:
    explicit SkinShop(Joueur* joueur);
    ~SkinShop();
    


private:
    int m_selectedSkinIndex;
    int w;
    Joueur* joueur;
    QGraphicsPixmapItem* cadre;
    QGraphicsTextItem* titre;
    QGraphicsTextItem* pieces;
    
    QGraphicsPixmapItem* imgpiece;
    QVBoxLayout* layout;
    QGraphicsView* view;
    QGraphicsScene* scene;
    QGraphicsPixmapItem* background;
    QGraphicsPixmapItem* vignes;
    QPushButton* exitButton;
    QWidget* buttonContainer;
    QHBoxLayout* buttonLayout;
    QVector<QGraphicsPixmapItem*> skinItems;
    
    

    void setupUI();
    void loadSkins();
    void displaySkins();

   

};
#endif // SKINSHOP_H