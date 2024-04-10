#include "affichagegui.h"
#include <QDebug>


AffichageGUI::AffichageGUI(Jeu* j, Menu* m) : Affichage(j, m) {
    // Scene du jeu
    _scene = new QGraphicsScene;
    _scene->setSceneRect(0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y);
    _scene->setBackgroundBrush(Qt::white);
    //QGraphicsPixmapItem* pixmap = new QGraphicsPixmapItem;
    //pixmap->setPixmap(QPixmap(":\\sprites\\Skins\\Monkey\\Monkey_Climb\\Monkey_Climb1.png"));
    //_scene->addItem(pixmap);

    // View du jeu
    setScene(_scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(WINDOW_SIZE_X, WINDOW_SIZE_Y);
    _background = new QGraphicsPixmapItem;
    _background->setPixmap(QPixmap(":\\sprites\\Background\\Background\\Background.png"));
    _background->setPos(0, (-_background->boundingRect().height() + WINDOW_SIZE_Y));
    _scene->addItem(_background);

    
    // Sprites des lianes
    for (int i = 0; i < NB_LIANES; i++) {
        int x = ((WINDOW_SIZE_X / 2) - (LARGEUR_LIANES / 2)) + (ESPACEMENT_LIANES * (i - 2));

        _lianes[i] = new QGraphicsPixmapItem;

        _lianes[i]->setPixmap(QPixmap(":\\sprites\\Background\\Vines\\Vine.png"));
        _lianes[i]->setPos(x, 0);
        _scene->addItem(_lianes[i]);
    }

    // Sprite du joueur
        _singe = new QGraphicsPixmapItem;
        _singe->setPixmap(QPixmap(":\\sprites\\Skins\\Monkey\\Monkey_Climb\\Monkey_Climb1.png"));
        _scene->addItem(_singe);

    // Menu pause
    _menuPause = new PauseMenuGui;
    _menuPause->sceneAjouter(_scene);

    // Score + pieces + item texte
    _score = new QGraphicsTextItem;
    _score->setFont(QFont("Arial", 20));
    _score->setPos(20, WINDOW_SIZE_Y - 60);
    _score->setDefaultTextColor(Qt::black);
    _scene->addItem(_score);

    _piece = new QGraphicsTextItem;
    _piece->setFont(QFont("Arial", 20));
    _piece->setPos(20, WINDOW_SIZE_Y - 100);
    _piece->setDefaultTextColor(Qt::black);
    _scene->addItem(_piece);

    _item = new QGraphicsTextItem;
    _item->setFont(QFont("Arial", 20));
    _item->setPos(WINDOW_SIZE_X - 140, WINDOW_SIZE_Y - 60);
    _item->setPlainText("ITEMS");
    _item->setDefaultTextColor(Qt::black);
    _scene->addItem(_item);

    // Fleches direction joueur
    _flecheGauche = new QGraphicsPixmapItem;
    _flecheGauche->setPixmap(QPixmap(":/sprites/UI/flecheGauche.png"));
    _flecheGauche->setVisible(false);
    _scene->addItem(_flecheGauche);

    _flecheDroite = new QGraphicsPixmapItem;
    _flecheDroite->setPixmap(QPixmap(":/sprites/UI/flecheDroite.png"));
    _flecheDroite->setVisible(false);
    _scene->addItem(_flecheDroite);

    // Items du joueur
    _itemCadre1 = new QGraphicsRectItem;
    _itemCadre1->setRect(0, 0, 75, 75);
    _itemCadre1->setPos(WINDOW_SIZE_X - 160, WINDOW_SIZE_Y - 150);
    _scene->addItem(_itemCadre1);

    _itemCadre2 = new QGraphicsRectItem;
    _itemCadre2->setRect(0, 0, 40, 40);
    _itemCadre2->setPos(WINDOW_SIZE_X - 70, WINDOW_SIZE_Y - 170);
    _scene->addItem(_itemCadre2);

    _item1 = new QGraphicsRectItem;
    int wc1 = _itemCadre1->boundingRect().width();
    int hc1 = _itemCadre1->boundingRect().height();
    int xc1 = _itemCadre1->x();
    int yc1 = _itemCadre1->y();
    _item1->setRect(0, 0, wc1 - (PADDING_ITEM_JOUEUR * 2), hc1 - (PADDING_ITEM_JOUEUR * 2));
    _item1->setPos(xc1 + PADDING_ITEM_JOUEUR, yc1 + PADDING_ITEM_JOUEUR);
    _scene->addItem(_item1);

    _item2 = new QGraphicsRectItem;
    int wc2 = _itemCadre2->boundingRect().width();
    int hc2 = _itemCadre2->boundingRect().height();
    int xc2 = _itemCadre2->x();
    int yc2 = _itemCadre2->y();
    _item2->setRect(0, 0, wc2 - (PADDING_ITEM_JOUEUR * 2), hc2 - (PADDING_ITEM_JOUEUR * 2));
    _item2->setPos(xc2 + PADDING_ITEM_JOUEUR, yc2 + PADDING_ITEM_JOUEUR);
    _scene->addItem(_item2);

    // Joueur audio
    _mediaPlayer = new QMediaPlayer;
    _audioOutput = new QAudioOutput;

    _mediaPlayer->setAudioOutput(_audioOutput);
    _mediaPlayer->setSource(QUrl("qrc:/music/monkeyClimb.mp3"));
    _audioOutput->setVolume(50);
    _mediaPlayer->setLoops(QMediaPlayer::Infinite);
    _mediaPlayer->play();

    // Time points
    _lastDustPuffSpawn = std::chrono::steady_clock::now();

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
    // Singe
    Coordonnee coord = transposerCoord(_jeu->getPositionJoueur(), _singe);
    _singe->setPos(coord.x, coord.y);

    // Nuages de poussiere (serpent)
    if (_jeu->getJsonSerial()->accShake() && canSpawnDustPuff())
        createDustPuff();

    for (int i = _dustPuffs.size() - 1; i >= 0; i--)
        updateDustPuff(i);
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
    // Texte score & piece
    _score->setPlainText(QString("Score: ") + QString::number(_jeu->getPointageJoueur()));
    _piece->setPlainText(QString("Pieces: ") + QString::number(_jeu->getPiecesJoueur()));

    // Items que le joueur a recolte
    char charItem1 = _jeu->getCharInventaire().item1;
    char charItem2 = _jeu->getCharInventaire().item2;

    if (charItem1 == '@') {
        _item1->setVisible(true);
        _item1->setBrush(Qt::cyan);
    }
    else if (charItem1 == 'B') {
        _item1->setVisible(true);
        _item1->setBrush(Qt::yellow);
    }
    else
        _item1->setVisible(false);

    if (charItem2 == '@') {
        _item2->setVisible(true);
        _item2->setBrush(Qt::cyan);
    }
    else if (charItem2 == 'B') {
        _item2->setVisible(true);
        _item2->setBrush(Qt::yellow);
    }
    else
        _item2->setVisible(false);

    // Fleches direction joueur
    if (_jeu->getJsonSerial()->joystickMaintenu(DROITE)) {
        _flecheDroite->setVisible(true);
        _flecheGauche->setVisible(false);
        _flecheDroite->setPos(_singe->x() + 75 - _singe->boundingRect().width(), _singe->y() - 2);
    }
    else if (_jeu->getJsonSerial()->joystickMaintenu(GAUCHE)) {
        _flecheGauche->setVisible(true);
        _flecheDroite->setVisible(false);
        _flecheGauche->setPos(_singe->x() - 75, _singe->y() - 2);
    }
    else {
        _flecheGauche->setVisible(false);
        _flecheDroite->setVisible(false);
    }
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
}

void AffichageGUI::updateGUI() {
    // afficherMenu();
    afficherJeu();
}

void AffichageGUI::updateItemGUI() {
    std::vector<ElementJeu*> elements = _jeu->getElements();

    // Enlever les items supprimes
    for (size_t i = 0; i < _itemsGui.size(); i++) // TODO - iteration inverse
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
            case BOUCLIER:      color = Qt::cyan;        break;
            case PIECE:         color = Qt::darkYellow;  break;
            case HARPIE:        color = Qt::lightGray;   break;
            case SERPENT:       color = Qt::green;       break;
        }
        _itemsGui[i].gui->setBrush(color);

        _scene->addItem(_itemsGui[i].gui);
    }
}

void AffichageGUI::createDustPuff() {
    QGraphicsPixmapItem* pixmap = new QGraphicsPixmapItem;
    QPointF centreSinge = _singe->pos() + _singe->boundingRect().center();
    int x = _randGen.random(centreSinge.x() - DIST_SPAWN_DUSTPUFF, centreSinge.x() + DIST_SPAWN_DUSTPUFF, rand());
    int y = _randGen.random(centreSinge.y() - DIST_SPAWN_DUSTPUFF, centreSinge.y() + DIST_SPAWN_DUSTPUFF, rand());
    int dustPuffType = _randGen.random(1, 3, rand());
    int startingRotation = _randGen.random(0, 359, rand());

    pixmap->setPixmap(QPixmap(QString(":/sprites/Effets/dustpuff") + QString::number(dustPuffType) + QString(".png")));
    pixmap->setPos(x - pixmap->boundingRect().width() / 2, y - pixmap->boundingRect().height() / 2);
    pixmap->setTransformOriginPoint(pixmap->boundingRect().width() / 2, pixmap->boundingRect().height() / 2);
    pixmap->setRotation(startingRotation);
    _scene->addItem(pixmap);

    _lastDustPuffSpawn = std::chrono::steady_clock::now();

    _dustPuffs.push_back({ pixmap, _lastDustPuffSpawn });
}

void AffichageGUI::updateDustPuff(int vecIndex) {
    DustPuff* puff = &_dustPuffs[vecIndex];
    auto now = std::chrono::steady_clock::now();
    auto duration = now - puff->spawnTime;
    double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

    if (elapsed > LIFESPAN_DUSTPUFF) {
        delete puff->pixmap;
        _dustPuffs.erase(_dustPuffs.begin() + vecIndex);
        return;
    }

    double scale = PEAK_SCALE_DUSTPUFF * sin((M_PI * elapsed) / 1000.0);
    puff->pixmap->setScale(scale);
    puff->pixmap->setRotation(puff->pixmap->rotation() + 1);
    return;
}

bool AffichageGUI::canSpawnDustPuff() {
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastDustPuffSpawn);
    return elapsed.count() > SPAWN_DELAY_DUSTPUFF;
}

Coordonnee AffichageGUI::transposerCoord(const Coordonnee& coord, QGraphicsItem* item) {
    int w = item->boundingRect().width();
    int h = item->boundingRect().height();
    int x = _lianes[coord.x]->x() - (w / 2) + (LARGEUR_LIANES / 2);
    int y = coord.y * (WINDOW_SIZE_Y / COORD_MAX_Y) - (h / 2);
    return { x, y };
}
