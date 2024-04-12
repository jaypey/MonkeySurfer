#ifndef SKINSHOP_H
#define SKINSHOP_H


#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsProxyWidget>
#include <QVector>
#include "joueur.h"
#include "skin.h"

// Forward declarations
class Menu;

class SkinShop : public QWidget
{
    Q_OBJECT
    
public:
    SkinShop(Joueur* joueur, Skin* skins, Menu* menu);
    ~SkinShop();
    void startTimer();
    void quitter();

public slots:
    void update();

   
private:
    QTimer* update_timer;
    Skin* skins;
    int m_selectedSkinIndex;
    int w;
    Menu* _m;
    Joueur* joueur;
    QGraphicsPixmapItem* _cadre;
    QGraphicsPixmapItem* _glow;
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
    QVector<QGraphicsTextItem*> _details;

    void setupUI();
    void displaySkins();


signals:
    void retourMenu();


};
#endif // SKINSHOP_H