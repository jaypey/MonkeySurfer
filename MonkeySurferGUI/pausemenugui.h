#ifndef PAUSEMENUGUI_H
#define PAUSEMENUGUI_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

#define PADDING_RECT_CHOIX 10.0 // Espacement entre texte et le rectangle de choix d'option

class PauseMenuGui {
public:
    PauseMenuGui();

    void sceneAjouter(QGraphicsScene* scene);
    void setVisible(bool visible);
    void setChoixOption(int choix);
private:
    QGraphicsRectItem* _cadre;
    QGraphicsRectItem* _choix;
    QGraphicsTextItem* _textePause;
    QGraphicsTextItem* _texteContinuer;
    QGraphicsTextItem* _texteRetourMenu;
};

#endif // !PAUSEMENUGUI_H
