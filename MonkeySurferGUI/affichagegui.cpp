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

    _backgroundLoop1 = new QGraphicsPixmapItem;
    _backgroundLoop1->setPixmap(QPixmap(":\\sprites\\Background\\Background\\Repeatable_space.png"));
    _backgroundLoop1->setPos(0, _background->y() - _backgroundLoop1->boundingRect().height());
    _scene->addItem(_backgroundLoop1);

    _backgroundLoop2 = new QGraphicsPixmapItem;
    _backgroundLoop2->setPixmap(QPixmap(":\\sprites\\Background\\Background\\Repeatable_space.png"));
    _backgroundLoop2->setPos(0, _backgroundLoop1->y() - _backgroundLoop2->boundingRect().height());
    _scene->addItem(_backgroundLoop2);

    // Sprite du joueur
    _singe = new AnimatedPixmap(150);
    _singe->addFrame(":\\sprites\\Skins\\Monkey\\Monkey_Climb\\Monkey_Climb1.png");
    _singe->addFrame(":\\sprites\\Skins\\Monkey\\Monkey_Climb\\Monkey_Climb2.png");
    _singe->addFrame(":\\sprites\\Skins\\Monkey\\Monkey_Climb\\Monkey_Climb3.png");
    _singe->addFrame(":\\sprites\\Skins\\Monkey\\Monkey_Climb\\Monkey_Climb4.png");
    _singe->setFrame(0);
    _scene->addItem(_singe);

    // Sprites des lianes
    for (int i = 0; i < NB_LIANES; i++) {
        int x = ((WINDOW_SIZE_X / 2) - (LARGEUR_LIANES / 2)) + (ESPACEMENT_LIANES * (i - 2));

        _lianes[i] = new QGraphicsPixmapItem;

        _lianes[i]->setPixmap(QPixmap(":\\sprites\\Background\\Vines\\Vine.png"));
        //_lianes[i]->setRect(0, 0, LARGEUR_LIANES, WINDOW_SIZE_Y);
        _lianes[i]->setPos(x, 0);
        _scene->addItem(_lianes[i]);
    }

    // Menu pause
    _menuPause = new PauseMenuGui;
    _menuPause->sceneAjouter(_scene);

    _menuGameover = new GameOverMenuGui(j);
    _menuGameover->sceneAjouter(_scene);

    // Score + pieces + item texte
    _piece = new QGraphicsTextItem;
    _piece->setFont(QFont("Jungle Fever NF", 40));
    _piece->setPos(45, WINDOW_SIZE_Y - 45 - _piece->boundingRect().height());
    _piece->setDefaultTextColor(Qt::white);
    _scene->addItem(_piece);

    _score = new QGraphicsTextItem;
    _score->setFont(QFont("Jungle Fever NF", 40));
    _score->setPos(45, WINDOW_SIZE_Y - 45 - _score->boundingRect().height() - _piece->boundingRect().height());
    _score->setDefaultTextColor(Qt::white);
    _scene->addItem(_score);

    _item = new QGraphicsTextItem;
    _item->setFont(QFont("Jungle Fever NF", 20));
    _item->setPos(WINDOW_SIZE_X - 140, WINDOW_SIZE_Y - 60);
    _item->setPlainText("ITEMS");
    _item->setDefaultTextColor(Qt::white);
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

    for (int i = 0; i < NB_LIANES; i++) {
        int x = ((WINDOW_SIZE_X / 2) - (LARGEUR_LIANES / 2)) + (ESPACEMENT_LIANES * (i - 2));

        _lianes[i] = new QGraphicsPixmapItem;

        _lianes[i]->setPixmap(QPixmap(":\\sprites\\Background\\Vines\\Vine.png"));
        //_lianes[i]->setRect(0, 0, LARGEUR_LIANES, WINDOW_SIZE_Y);
        _lianes[i]->setPos(x, 0);
        _scene->addItem(_lianes[i]);
    }

    // Items du joueur
    _itemCadre1 = new QGraphicsPixmapItem;
    _itemCadre1->setPixmap(QPixmap(":/sprites/UI/cadrevigne.png"));
    _itemCadre1->setPos(WINDOW_SIZE_X - 350, WINDOW_SIZE_Y - 250);
    _scene->addItem(_itemCadre1);

    _itemCadre2 = new QGraphicsPixmapItem;
    _itemCadre2->setPixmap(QPixmap(":/sprites/UI/cadrevigne.png"));
    _itemCadre2->setScale(0.8);
    _itemCadre2->setPos(WINDOW_SIZE_X - 170, WINDOW_SIZE_Y - 270);
    _scene->addItem(_itemCadre2);

    _item1 = new QGraphicsPixmapItem;
    int wc1 = _itemCadre1->boundingRect().width();
    int hc1 = _itemCadre1->boundingRect().height();
    int xc1 = _itemCadre1->x();
    int yc1 = _itemCadre1->y();
    _item1->setPos(xc1 + PADDING_ITEM1_JOUEUR, yc1 + PADDING_ITEM1_JOUEUR);
    _scene->addItem(_item1);

    _item2 = new QGraphicsPixmapItem;
    int wc2 = _itemCadre2->boundingRect().width() * 0.8;
    int hc2 = _itemCadre2->boundingRect().height() * 0.8;
    int xc2 = _itemCadre2->x();
    int yc2 = _itemCadre2->y();
    _item2->setPos(xc2 + PADDING_ITEM2_JOUEUR, yc2 + PADDING_ITEM2_JOUEUR);
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

    // Quand le singe bouge on part l'animation
    QObject::connect(_jeu->getJoueur(), SIGNAL(mouvementSinge()), this, SLOT(mouvementSinge()));
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

void AffichageGUI::mouvementSinge() {
    _singe->setLoops(1);
}

void AffichageGUI::afficherArrierePlan() {
    int mouvementBg = std::max(1.0, (1000.0 - _jeu->getVitesse()) / 100.0);

    _background->setPos(0, _background->y() + mouvementBg);
    _backgroundLoop1->setPos(0, _backgroundLoop1->y() + mouvementBg);
    _backgroundLoop2->setPos(0, _backgroundLoop2->y() + mouvementBg);

    if (_backgroundLoop1->y() > WINDOW_SIZE_Y)
        _backgroundLoop1->setPos(0, _backgroundLoop2->y() - _backgroundLoop1->boundingRect().height());

    if (_backgroundLoop2->y() > WINDOW_SIZE_Y)
        _backgroundLoop2->setPos(0, _backgroundLoop1->y() - _backgroundLoop2->boundingRect().height());
}

void AffichageGUI::afficherLianes() {
    int tickCount = _jeu->getTickTockWahHooCount();

    // Sprites des lianes
    for (int i = 0; i < NB_LIANES; i++) {
        int x = ((WINDOW_SIZE_X / 2) - (LARGEUR_LIANES / 2)) + (ESPACEMENT_LIANES * (i - 2));
        _lianes[i]->setPos(x, tickCount);
    }
}

void AffichageGUI::afficherJoueur() {
    // Singe
    Coordonnee coord = transposerCoord(_jeu->getPositionJoueur(), _singe);
    _singe->setPos(coord.x, coord.y);
    _singe->animate();

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
        QGraphicsPixmapItem* rect = _itemsGui[i].gui;
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
        _item1->setPixmap(QPixmap(":/sprites/Objets/Bouclier/bigBubble.png"));
    }
    else if (charItem1 == 'B') {
        _item1->setVisible(true);
        _item1->setPixmap(QPixmap(":/sprites/Objets/Banane/bigBanana.png"));
    }
    else
        _item1->setVisible(false);

    if (charItem2 == '@') {
        _item2->setVisible(true);
        _item2->setPixmap(QPixmap(":/sprites/Objets/Bouclier/bubble.png"));
    }
    else if (charItem2 == 'B') {
        _item2->setVisible(true);
        _item2->setPixmap(QPixmap(":/sprites/Objets/Banane/banana.png"));
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
    if (_jeu->isGameOver())
    {
        _menuGameover->setPiece();
        _menuGameover->setScore();
        _menuGameover->setVisible(true);
        _score->setVisible(false);
        _piece->setVisible(false);
        _item1->setVisible(false);
        _item2->setVisible(false);
        _itemCadre1->setVisible(false);
        _itemCadre2->setVisible(false);
        _item->setVisible(false);
        _menuGameover->setChoixOption(_jeu->getGameOverOption());
    }
    else
    {
        _menuGameover->setVisible(false);
    }
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

    if (_menu->getEtat() == Menu::EtatMenu::JEU) {
        _jeu->debuterPartie();
    }
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
        _itemsGui.push_back({ elements[i], new QGraphicsPixmapItem });

        QString pixmap;
        switch (_itemsGui[i].item->getID()) {
            case OBSTACLE_FIXE: pixmap = ":/sprites/Objets/Ruche/ruche.png";        break;
            case BANANE:        pixmap = ":/sprites/Objets/Banane/banana.png";      break;
            case BOUCLIER:      pixmap = ":/sprites/Objets/Bouclier/bubble.png";    break;
            case PIECE:         pixmap = ":/sprites/Objets/Piece/coin.png";         break;
            case HARPIE:        pixmap = ":/sprites/Objets/Harpie/harpie.png";      break;
            case SERPENT:       pixmap = ":/sprites/Objets/Serpent/snake.png";      break;
        }
        _itemsGui[i].gui->setPixmap(QPixmap(pixmap));

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
