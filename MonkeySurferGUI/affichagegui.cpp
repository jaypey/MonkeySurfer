#include "affichagegui.h"
#include <QDebug>


AffichageGUI::AffichageGUI(Jeu* j, Menu* m) : Affichage(j, m) {
    // Scene du jeu
    _scene = new QGraphicsScene;
    _scene->setSceneRect(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y);
    QGraphicsPixmapItem* pixmap = new QGraphicsPixmapItem;
    pixmap->setPixmap(QPixmap(":\\sprites\\Skins\\Monkey\\Monkey_Climb\\Monkey_Climb1.png"));
    _scene->addItem(pixmap);

    // View du jeu
    setScene(_scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);

    // Sprite du joueur
    _singe = new QGraphicsRectItem;
    _singe->setRect(0, 0, 40, 40);
    _scene->addItem(_singe);

    // Sprites des lianes
    for (int i = 0; i < NB_LIANES; i++) {
        int x = ((WINDOW_SIZE_X / 2) - (LARGEUR_LIANES / 2)) + (ESPACEMENT_LIANES * (i - 2));

        _lianes[i] = new QGraphicsRectItem;
        _lianes[i]->setRect(0, 0, LARGEUR_LIANES, WINDOW_SIZE_Y);
        _lianes[i]->setPos(x, 0);
        _scene->addItem(_lianes[i]);
    }

    // Menu pause
    _menuPause = new PauseMenuGui;
    _menuPause->sceneAjouter(_scene);

    // Timer qui update automatiquement le jeu ainsi que les graphiques Qt
    _updateTimer = new QTimer;
    QObject::connect(_updateTimer, SIGNAL(timeout()), this, SLOT(update()));
    _updateTimer->start(1000 / FPS); // Nb ms par frame
}

void AffichageGUI::afficherJeu() {
    afficherArrierePlan();
    afficherLianes();
    afficherJoueur();
    afficherItems();
    afficherIU();
    afficherGameOver();
    afficherPause();
}

void AffichageGUI::afficherMenu() {

}

void AffichageGUI::update() {
    updateJeu();
    updateGUI();
}

void AffichageGUI::afficherArrierePlan() {

}

void AffichageGUI::afficherLianes() {

}

void AffichageGUI::afficherJoueur() {
    Coordonnee coord = transposerCoord(_jeu->getPositionJoueur(), _singe);
    _singe->setPos(coord.x, coord.y);
}

void AffichageGUI::afficherItems() {
    updateItemGUI();

    for (size_t i = 0; i < _itemsGui.size(); i++) {
        ElementJeu* item = _itemsGui[i].item;
        QGraphicsRectItem* rect = _itemsGui[i].gui;
        Coordonnee coord = transposerCoord(item->getPosition(), rect);

        // Offset si l'harpie est en mode "avertissement"
        if (item->getID() == HARPIE) {
            HarpieFeroce* harpie = static_cast<HarpieFeroce*>(item);
            if (harpie->getAvertissement() == true) {
                if (harpie->getPosition().x == 0)
                    coord.x -= ESPACEMENT_LIANES;
                else if (harpie->getPosition().x == 4)
                    coord.x += ESPACEMENT_LIANES;
            }
        }

        rect->setPos(coord.x, coord.y);
    }
}

void AffichageGUI::afficherIU() {

}

void AffichageGUI::afficherGameOver() {

}

void AffichageGUI::afficherPause() {
    if (_jeu->isPaused()) {
        _menuPause->setVisible(true);
        _menuPause->setChoixOption(_jeu->getPauseOption());
    }
    else
        _menuPause->setVisible(false);
}

void AffichageGUI::updateJeu() {
    _jeu->getJsonSerial()->sendJson();
    _jeu->getJsonSerial()->recvJson();

    _jeu->debuterPartie();
    qDebug() << _jeu->getPointageJoueur() << ", " << _jeu->getPositionJoueur().x;
}

void AffichageGUI::updateGUI() {
    // afficherMenu();
    afficherJeu();
}

void AffichageGUI::updateItemGUI() {
    std::vector<ElementJeu*> elements = _jeu->getElements();

    // Enlever les items supprimes
    for (size_t i = 0; i < _itemsGui.size(); i++)
        if (i >= elements.size() || _itemsGui[i].item != elements[i]) {
            delete _itemsGui[i].gui;
            _itemsGui.erase(_itemsGui.begin() + i);
            i--;
        }

    // Ajouter les nouveaux items
    for (size_t i = _itemsGui.size(); i < elements.size(); i++) {
        QGraphicsRectItem* rect = new QGraphicsRectItem;
        _itemsGui.push_back({ elements[i], new QGraphicsRectItem });
        _itemsGui[i].gui->setRect(0, 0, 25, 25);

        Qt::GlobalColor color = Qt::white;
        switch (_itemsGui[i].item->getID()) {
            case OBSTACLE_FIXE: color = Qt::red;         break;
            case BANANE:        color = Qt::yellow;      break;
            case BOUCLIER:      color = Qt::blue;        break;
            case PIECE:         color = Qt::darkYellow;  break;
            case HARPIE:        color = Qt::lightGray;   break;
            case SERPENT:       color = Qt::green;       break;
        }
        _itemsGui[i].gui->setBrush(color);

        _scene->addItem(_itemsGui[i].gui);
    }
}

Coordonnee AffichageGUI::transposerCoord(const Coordonnee& coord, QGraphicsItem* item) {
    int w = item->boundingRect().width();
    int h = item->boundingRect().height();
    int x = _lianes[coord.x]->x() - (w / 2) + (LARGEUR_LIANES / 2);
    int y = coord.y * (WINDOW_SIZE_Y / COORD_MAX_Y) - (h / 2);
    return { x, y };
}
