#ifndef MULTIJOUEURLOBBY_H
#define MULTIJOUEURLOBBY_H


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


class MultijoueurLobby : public QWidget
{
    Q_OBJECT

public:
    explicit MultijoueurLobby(Joueur* joueur);
    ~MultijoueurLobby();

public slots:
    void updateConnectedPlayers(int playerCount);

private:
    int m_selectedSkinIndex;
    int m_playerCount;
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


};
#endif // MultijoueurLobby_H