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
#include "menu.h"
#include "skin.h"


class SkinShop : public QWidget
{
    Q_OBJECT
    
public:
    explicit SkinShop(Joueur* joueur, Skin* skins);
    ~SkinShop();
    


private:
    Skin* skins;
    int m_selectedSkinIndex;
    int w;
    Joueur* joueur;
    QGraphicsPixmapItem* _cadre;
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


signals:
    void retourMenu();


};
#endif // SKINSHOP_H