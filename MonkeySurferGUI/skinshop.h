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

signals:
    void skinChosen(const Skin& skin);

public slots:
    void setVisible(bool visible);

protected:
    void keyPressEvent(QKeyEvent* event);

private:
    QGraphicsView* m_graphicsView;
    QGraphicsScene* m_scene;
    QVector<Skin> m_skins;
    int m_selectedSkinIndex;

    void loadSkins();
    void displaySkinPreview();
};

#endif // SKINSHOP_H