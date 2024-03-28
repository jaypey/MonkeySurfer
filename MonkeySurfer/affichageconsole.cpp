#include "affichageconsole.h"

AffichageConsole::AffichageConsole(Jeu *j, Menu *m) : Affichage(j, m) {
    _lastfrm = std::chrono::steady_clock::now();
    _lastupdate = std::chrono::steady_clock::now();
    initialiserLianes();
    afficherArrierePlan();
}

AffichageConsole::~AffichageConsole() {}

void AffichageConsole::afficherJeu() {
    attendreProchaineImage();

    updateDeco();

    // Remplissage des informations dans la matrice de char
    afficherArrierePlan();
    afficherLianes();
    afficherJoueur();
    afficherItems();
    afficherContour();
    afficherIU();
    if (_jeu->isGameOver()) {
        afficherGameOver();
    }
    else if (_jeu->isPaused()) {
        afficherPause();
    }

    // Print � la console
    printMatriceChar();
}

void AffichageConsole::afficherMenu() {
    attendreProchaineImage();

    switch (_menu->getEtat()) {
        case Menu::EtatMenu::PRINCIPAL: afficherMenuPrincipal(); break;
        case Menu::EtatMenu::SKINS: afficherMenuSkin(); break;
        case Menu::EtatMenu::AIDE: afficherAide(); break;
        case Menu::EtatMenu::CHARGEMENT: afficherLoading(); break;
    }

    printMatriceChar();
}

void AffichageConsole::afficherMenuPrincipal() {
    int cm = _menu->getChoixMenu();

    afficherArrierePlan();
    afficherContour();
    afficherFichier("artMenu.txt", 5, 2);
    afficherFichier("monkey.txt", 43, 4, CMD_MONKEY_COLOR);
    afficherTexte("1. Jouer", 25, 15, CMD_WHITE, (cm == 0));
    afficherTexte("2. Skins", 25, 17, CMD_WHITE, (cm == 1));
    afficherTexte("3. Aide", 25, 19, CMD_WHITE, (cm == 2));
    afficherTexte("4. Quitter", 25, 21, CMD_WHITE, (cm == 3));
}

void AffichageConsole::afficherMenuSkin() {
    // Remplissage des informations dans la matrice de char
    afficherArrierePlan();
    afficherContour();

    std::string textPrix;

    // Affichage de la shop
    for (int rangee = 0; rangee < 3; rangee++)
        for (int col = 0; col < 3; col++) {
            int index = col + rangee * 3;

            std::string apparence;
            apparence += _menu->getSkin(index).getId();

            std::string fichierBox;
            CMDColor couleurBox;

            // Fichier art box skin
            fichierBox = (_menu->getIndexSkin() == index) ? "showcaseSkinSelect.txt" : "showcaseSkin.txt";

            // Couleur + Prix case
            if (_menu->getSkin(index).isDebloque())
                if (_menu->getIndexSkinPreview() == index) {
                    couleurBox = CMD_WHITE;
                    textPrix = "Debloque";
                }
                else {
                    couleurBox = CMD_CONTOUR_COLOR;
                }
            else if (_menu->getIndexSkinPreview() == index) {
                couleurBox = CMD_SKIN_SELECT_BLOQUE_COLOR;
                textPrix = std::to_string(_menu->getSkin(index).getPrix());
            }
            else {
                couleurBox = CMD_SKIN_BLOQUE_COLOR;
            }

            // Afficher box
            afficherFichier(fichierBox, 8 + col * ECART_COL_SKINS, 2 + rangee * ECART_RANGEE_SKINS, couleurBox);
            afficherTexte(apparence, 12 + col * ECART_COL_SKINS, 4 + rangee * ECART_RANGEE_SKINS, CMD_MONKEY_COLOR);
        }

    std::string apparenceCourante = "Skin choisi : ";
    apparenceCourante += _menu->getSkin(_menu->getIndexSkin()).getId();

    std::string infoPrix = "Pieces : " + std::to_string(_jeu->getPiecesJoueur()) + " | Prix : " + textPrix;

    afficherTexte(apparenceCourante, 22, 20);
    afficherTexte(infoPrix, 18, 21);
    afficherTexte("'Btn3' acheter/choisir, Joystick select, 'Btn2' quitter", 3, 22);
}

void AffichageConsole::afficherAide() {
    // Remplissage des informations dans la matrice de char
    afficherArrierePlan();
    afficherContour();

    // Affichage du tutoriel
    std::string explicationSinge = " : Represente le singe (le joueur).";
    explicationSinge.insert(explicationSinge.begin(), _menu->getSkin(_menu->getIndexSkin()).getId());

    afficherTexte(explicationSinge, 3, 3);

    afficherTexte("X", 3, 5, CMD_OBSTACLE_COLOR);
    afficherTexte(" : Les obstacles, le singe doit les eviter!", 4, 5);

    afficherTexte("S", 3, 7, CMD_SERPENT_COLOR);
    afficherTexte(" : Les serpents, lorsqu'un vous attrape, secouez la", 4, 7);
    afficherTexte("    manette pour lui donner des coups de pied!", 3, 8);

    afficherTexte("H", 3, 10, CMD_HARPIE_COLOR);
    afficherTexte(" : Les harpies, elles ne doivent pas vous attraper!", 4, 10);

    afficherTexte("B", 3, 12, CMD_BANANE_COLOR);
    afficherTexte(" : Les bananes, ramassez les pour aller plus vite!", 4, 12);

    afficherTexte("$", 3, 14, CMD_PIECE_COLOR);
    afficherTexte(" : Les pieces, ramassez les pour accumuler des points!", 4, 14);

    afficherTexte("Le joystick determine la direction du saut, 'Btn3'", 3, 16);
    afficherTexte("fait sauter le singe aux autres lianes.", 3, 17);

    afficherTexte("Appuyer sur 'Btn2' pour revenir au menu.", 11, 21);
}

void AffichageConsole::afficherLoading() {
    // Gros monkey qui bondit sur l'�cran
    // Le code ci-dessous simule un monkey avec des physiques
    // qui bondit de gauche � droite & vice-versa, avec velocite
    // et vitesse pour d�terminer la vitesse de chute

    const int TAILLE_X = 14;
    const int TAILLE_Y = 8;
    const int VEL_X = 0;
    const int VEL_Y = 1;

    // "static" veut dire qu'� chaque appel de la fonction, les variables
    // gardent les m�mes valeurs qu'elles avaient � la fin de l'ex�cution
    // de l'appel de la fonction pr�c�dent
    static int spdX = 2;
    static int spdY = 0;
    static int posX = 0;
    static int posY = 5;

    spdX += VEL_X;
    spdY += VEL_Y;

    if (posX + spdX > NB_COLS - TAILLE_X - 1 || posX + spdX < 1) spdX = -spdX;
    else posX += spdX;

    if (posY + spdY > NB_LIGNES - TAILLE_Y - 1 || posY + spdY < 1) spdY = -spdY;
    else posY += spdY;

    afficherArrierePlan();
    afficherContour();
    afficherFichier("monkey.txt", posX, posY, CMD_MONKEY_COLOR);
    afficherTexte("Chargement...", 25, 2);
}

void AffichageConsole::initialiserLianes() {
    int milieu = NB_COLS / 2;

    // Positionnement des lianes, centr� dans la zone de jeu
    for (int i = 0; i < NB_LIANES; i++) {
        int multiple_offset = i - (NB_LIANES / 2);
        _xlianes[i] = milieu + (ECART_LIANES * multiple_offset);

        // Position des feuilles des lianes
        if (i % 2 == 0) {
            _feuilles[i][0] = { _xlianes[i] - 1, 5 };
            _feuilles[i][1] = { _xlianes[i] + 1, 11 };
            _feuilles[i][2] = { _xlianes[i] - 1, 19 };
        }
        else {
            _feuilles[i][0] = { _xlianes[i] + 1, 4 };
            _feuilles[i][1] = { _xlianes[i] - 1, 12 };
            _feuilles[i][2] = { _xlianes[i] + 1, 18 };
        }
    }
}

void AffichageConsole::afficherArrierePlan() {
    for (int y = 0; y < NB_LIGNES; y++)
        for (int x = 0; x < NB_COLS; x++)
            _img[x][y] = { ' ', CMD_WHITE };
}

void AffichageConsole::afficherLianes() {
    for (int i = 0; i < NB_LIANES; i++) {
        // Lianes
        for (int y = 0; y < NB_LIGNES; y++)
            _img[_xlianes[i]][y] = { 'l', CMD_LIANE_COLOR };
    
        // Feuilles
        for (int f = 0; f < 3; f++) {
            int fx = _feuilles[i][f].x;
            int fy = _feuilles[i][f].y;
            _img[fx][fy] = { '~', CMD_LIANE_COLOR };
        }
    }
}

void AffichageConsole::afficherJoueur() {
    Coordonnee positionCourante = _jeu->getPositionJoueur();
    int y = _jeu->getPositionJoueur().y;
    int x = _xlianes[positionCourante.x];

    CMDColor monkey;
    if (_jeu->isProtected())
    {
        monkey = CMD_BOUCLIER_COLOR;
    }
    else if (_jeu->isStuck())
    {
        monkey = CMD_SERPENT_COLOR;
    }
    else if (_jeu->isBoosted())
    {
        monkey = CMD_BANANE_COLOR;
    }
    else 
    {
        monkey = CMD_MONKEY_COLOR;
    }


    _img[x][y] = { _menu->getSkin(_menu->getIndexSkin()).getId(), monkey }; // monkey

    // Fleche direction de saut
    if (_jeu->getJsonSerial()->joystickMaintenu(DROITE)) {
        _img[x + 3][y] = { '>', CMD_WHITE };
        _img[x + 2][y] = { '-', CMD_WHITE };
    }
    else if (_jeu->getJsonSerial()->joystickMaintenu(GAUCHE)) {
        _img[x - 3][y] = { '<', CMD_WHITE };
        _img[x - 2][y] = { '-', CMD_WHITE };
    }

    else if (_jeu->getJsonSerial()->joystickMaintenu(HAUT)) {
        _img[x][y + 3] = { 'v', CMD_WHITE };
        _img[x][y + 2] = { '|', CMD_WHITE };
    }
    else if (_jeu->getJsonSerial()->joystickMaintenu(BAS)) {
        _img[x][y - 3] = { '^', CMD_WHITE };
        _img[x][y - 2] = { '|', CMD_WHITE };
    }
    // Poussieres et eclats s'il attaque le serpent
    if (_jeu->getJsonSerial()->accShake() || _jeu->isAttacking()) {
        _img[x-1][y-1] = getCharEclat();
        _img[x]  [y-1] = getCharEclat();
        _img[x+1][y-1] = getCharEclat();
        _img[x-1][y] = getCharEclat();
        _img[x+1][y] = getCharEclat();
        _img[x-1][y+1] = getCharEclat();
        _img[x]  [y+1] = getCharEclat();
        _img[x+1][y+1] = getCharEclat();
        _jeu->setIsAttacking(false);
    }
}

void AffichageConsole::afficherItems() {
    ElementJeu* elementCourant;
    for (int i = 0; i < _jeu->getElements().size(); i++) {
        elementCourant = _jeu->getElements()[i];

        // On affiche pas les objets hors jeu
        if (elementCourant->getPosition().y >= NB_LIGNES)
            continue;

        CharInfo visuel;
        switch (elementCourant->getID())
        {
        case OBSTACLE_FIXE:
            visuel = {'X', CMD_OBSTACLE_COLOR};
            break;
        case HARPIE:
            visuel = {'=', CMD_HARPIE_COLOR};
            break;
        case SERPENT:
            visuel = {'S', CMD_SERPENT_COLOR};
            break;
        case PIECE:
            visuel = {'$', CMD_PIECE_COLOR};
            break;
        case BOUCLIER:
            visuel = {'@', CMD_BOUCLIER_COLOR};
            break;
        case BANANE:
            visuel = {'B', CMD_BANANE_COLOR};
            break;

        default:
            visuel = {'l', CMD_LIANE_COLOR};
        }
        _img[_xlianes[elementCourant->getPosition().x]][elementCourant->getPosition().y] = visuel;
    }
    
}

void AffichageConsole::afficherIU() {
    // Vider l'espace pour afficher le texte clairement
    for (int i = 1; i < NB_COLS - 1; i++) {
        _img[i][NB_LIGNES - 2] = { ' ', CMD_CONTOUR_COLOR };
        _img[i][NB_LIGNES - 3] = { '=', CMD_CONTOUR_COLOR };
    }

    // Afficher le texte pour le score
    _score = "Score : " + std::to_string(_jeu->getPointageJoueur()) + " Pieces : " + std::to_string(_jeu->getPiecesJoueur());
    _inv = "Inventaire :  1 - " + std::string(1, _jeu->getCharInventaire().item1) + "   2 - " + std::string(1, _jeu->getCharInventaire().item2);

    afficherTexte(_score, 2, NB_LIGNES - 2);
    afficherTexte(_inv, 30, NB_LIGNES - 2);
}

void AffichageConsole::afficherGameOver() {
    afficherFichier("gameOver.txt", 3, 4);
    afficherFichier("retryText.txt", 7, 18);
}

void AffichageConsole::afficherPause() {
    int po = _jeu->getPauseOption();

    afficherFichier("pause.txt", 4, 4);
    afficherTexte("1. Continuer", 25, 13, CMD_WHITE, (po == 0));
    afficherTexte("2. Retourner au menu", 21, 15, CMD_WHITE, (po == 1));
}

void AffichageConsole::afficherContour() {
    // Coutour zone de jeu + UI
    for (int i = 0; i < NB_COLS; i++) {
        _img[i][0] = { '-', CMD_CONTOUR_COLOR };
        _img[i][NB_LIGNES - 1] = { '-', CMD_CONTOUR_COLOR };
    }
    for (int i = 1; i < NB_LIGNES - 1; i++) {
        _img[0][i] = { '|', CMD_CONTOUR_COLOR };
        _img[NB_COLS - 1][i] = { '|', CMD_CONTOUR_COLOR };
    }
}

void AffichageConsole::afficherTexte(std::string s, int x, int y, CMDColor color, bool selected) {
    if (selected) {
        _img[x - 2][y] = { '>', CMD_CONTOUR_COLOR };
        _img[x + s.size() + 1][y] = {'<', CMD_CONTOUR_COLOR};
    }

    for (int i = 0; i < s.size() && x + i < NB_COLS; i++)
        _img[x + i][y] = { s[i], color };
}

void AffichageConsole::afficherFichier(std::string nom, int x, int y, CMDColor color) {
    std::ifstream fichier("ascii/" + nom);
    std::string texte;

    while (std::getline(fichier, texte) && y < NB_LIGNES)
        afficherTexte(texte, x, y++, color);
}

void AffichageConsole::updateDeco() {
    //auto now = std::chrono::steady_clock::now();
    //auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastupdate);
    if (_lastupdate < _jeu->getLastUpdate()) {
        for (int x = 0; x < NB_LIANES; x++)
            for (int f = 0; f < 3; f++)
                _feuilles[x][f].y = (_feuilles[x][f].y + 1) % 23;
        _lastupdate = _jeu->getLastUpdate();
    }
}

void AffichageConsole::printMatriceChar() {
    // Transposition des informations de la matrice de char dans une seule std::string pour tout imprimer
    // � la console d'un seul coup avec un seul appel de std::cout (very fast)
    CMDColor currcolor = { -1, -1, -1 };
    _output.clear(); // Supprime le contenu de l'ancienne image dans la std::string
    std::cout << "\x1b[0;0H"; // Curseur position (0, 0) - ANSI escape sequence
    for (int y = 0; y < NB_LIGNES; y++) {
        for (int x = 0; x < NB_COLS; x++) {
            // Appliquer couleur
            if (_img[x][y].color != currcolor) {
                currcolor = _img[x][y].color;
                _output += currcolor.to_string();
            }

            // Ajouter caractere a la std::string
            _output += _img[x][y].c;
        }
        _output += '\n';
    }
    std::cout << _output; // Imprime l'image � la console
}

CharInfo AffichageConsole::getCharEclat() {
    // 50% chance d'afficher un eclat, 50% d'afficher rien
    // * # @
    // 0 1 2 3 4 5
    switch (_rand.random(0, 5, rand())) {
        case 0: return { '*', CMD_ECLAT_COLOR };
        case 1: return { '#', CMD_ECLAT_COLOR };
        case 2: return { '&', CMD_ECLAT_COLOR };
    }
    return { ' ', CMD_ECLAT_COLOR };
}

bool AffichageConsole::peutAfficherProchaineImage() {
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastfrm);
    return elapsed.count() > _DURFRM; // S'assure que suffisamment de temps s'est �coul� depuis le dernier affichage (dur�e bas�e sur le FPS)
}

void AffichageConsole::attendreProchaineImage() {
    while (!peutAfficherProchaineImage()); // Attendre de pouvoir afficher la prochaine image
    _lastfrm = std::chrono::steady_clock::now(); // Update du temps de la derni�re image
}
