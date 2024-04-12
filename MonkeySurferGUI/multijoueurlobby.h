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
#include "menu.h"
#include <QTimer>
#include "affichagegui.h"


class MultijoueurLobby : public QWidget
{
    Q_OBJECT

public:
    explicit MultijoueurLobby(Menu* menu, AffichageGUI* affi);
    ~MultijoueurLobby();

public slots:
    void updateConnectedPlayers();
    void startUpdateLoop();
    void updateNetwork();

private:
    int m_selectedSkinIndex;
    int m_playerCount;
    AffichageGUI* _affichage;
    Menu* _menu;
    QTimer* _timer;
    QGraphicsPixmapItem* cadre;
    QGraphicsTextItem* titre;
    QGraphicsTextItem* messagePret;
    QGraphicsTextItem* messagePretOui;

    QGraphicsPixmapItem* imgpiece;
    QVBoxLayout* layout;
    QGraphicsView* view;
    QGraphicsScene* scene;
    QGraphicsPixmapItem* background;
    QGraphicsPixmapItem* vignes;
    QPushButton* exitButton;
    QWidget* buttonContainer;
    QHBoxLayout* buttonLayout;

    void setupUI();
protected:
    void keyPressEvent(QKeyEvent* event) override
    {
        if (event->key() == Qt::Key_R)
        {
            _menu->updateEtatReady();
            messagePretOui->setPlainText(QString("Vous etes pret"));
        }
    }




};
#endif // MultijoueurLobby_H