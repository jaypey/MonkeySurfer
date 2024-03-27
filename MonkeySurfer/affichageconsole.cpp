#include "affichageconsole.h"

AffichageConsole::AffichageConsole(Jeu *j, Menu *m) : Affichage(j, m) {
    _lastfrm = std::chrono::steady_clock::now();
    _lastupdate = std::chrono::steady_clock::now();
    initialiserLianes();
    initialiserSkins();
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

    // Print à la console
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
    afficherFichier("monkey.txt", 43, 4);
    afficherTexte("1. Jouer", 25, 15, (cm == 0));
    afficherTexte("2. Skins", 25, 17, (cm == 1));
    afficherTexte("3. Aide", 25, 19, (cm == 2));
    afficherTexte("4. Quitter", 25, 21, (cm == 3));
}

void AffichageConsole::afficherMenuSkin() {
    // Remplissage des informations dans la matrice de char
    afficherArrierePlan();
    afficherContour();

    // Affichage de la shop
    for (int rangee = 0; rangee < 3; rangee++)
        for (int col = 0; col < 3; col++) {
            int index = col + rangee * 3;

            std::string apparence;
            apparence += _skins[index].getId();

            const char* fichier = (_menu->getIndexSkin() == index)
                                ? "showcaseSkinSelect.txt"
                                : "showcaseSkin.txt";
            afficherFichier(fichier, 8 + col * ECART_COL_SKINS, 2 + rangee * ECART_RANGEE_SKINS);
            afficherTexte(apparence, 12 + col * ECART_COL_SKINS, 4 + rangee * ECART_RANGEE_SKINS);
        }

    std::string apparenceCourante = "Skin choisi : ";
    apparenceCourante += _skins[_menu->getIndexSkin()].getId();
    afficherTexte(apparenceCourante, 22, 20);

    afficherTexte("Appuyer sur les fleches pour choisir un skin", 7, 21);
    afficherTexte("Appuyer sur 'q' pour quitter", 15, 22);
}

void AffichageConsole::afficherAide() {
    // Remplissage des informations dans la matrice de char
    afficherArrierePlan();
    afficherContour();

    // Affichage du tutoriel
    std::string explicationSinge = " : Represente le singe (le joueur).";
    explicationSinge.insert(explicationSinge.begin(), _skins[_menu->getIndexSkin()].getId());

    afficherTexte(explicationSinge, 3, 3);

    afficherTexte("# : Les obstacles, le singe doit les eviter!", 3, 5);

    afficherTexte("B : Les bananes, ramassez les pour accumuler des points!", 3, 7);

    afficherTexte("Appuyer sur les fleches pour sauter de liane en liane.", 3, 9);

    afficherTexte("Une apparence differente peut etre choisie pour le singe", 3, 11);
    afficherTexte("dans le menu de skins, accessible par le menu principal.", 3, 12);

    afficherTexte("Appuyer sur 'q' pour revenir au menu.", 12, 21);
}

void AffichageConsole::afficherLoading() {
    // Gros monkey qui bondit sur l'écran
    // Le code ci-dessous simule un monkey avec des physiques
    // qui bondit de gauche à droite & vice-versa, avec velocite
    // et vitesse pour déterminer la vitesse de chute

    const int TAILLE_X = 14;
    const int TAILLE_Y = 8;
    const int VEL_X = 0;
    const int VEL_Y = 1;

    // "static" veut dire qu'à chaque appel de la fonction, les variables
    // gardent les mêmes valeurs qu'elles avaient à la fin de l'exécution
    // de l'appel de la fonction précédent
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
    afficherFichier("monkey.txt", posX, posY);
    afficherTexte("Chargement...", 25, 2);
}

void AffichageConsole::initialiserLianes() {
    int milieu = NB_COLS / 2;

    // Positionnement des lianes, centré dans la zone de jeu
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

void AffichageConsole::initialiserSkins() {
    char apparence[9] = { 'M', '#', 'W', 'O', 'X', 'T', 'U', 'A', '8' };
    for (int i = 0; i < 9; i++)
        _skins[i].setId(apparence[i]);
}

void AffichageConsole::afficherArrierePlan() {
    for (int y = 0; y < NB_LIGNES; y++)
        for (int x = 0; x < NB_COLS; x++)
            _img[x][y] = ' ';
}

void AffichageConsole::afficherLianes() {
    for (int i = 0; i < NB_LIANES; i++) {
        // Lianes
        for (int y = 0; y < NB_LIGNES; y++)
            _img[_xlianes[i]][y] = 'l';
    
        // Feuilles
        for (int f = 0; f < 3; f++) {
            int fx = _feuilles[i][f].x;
            int fy = _feuilles[i][f].y;
            _img[fx][fy] = '~';
        }
    }
}

void AffichageConsole::afficherJoueur() {
    Coordonnee positionCourante = _jeu->getPositionJoueur();
    int x = _xlianes[positionCourante.x];
    std::cout << std::endl << x;
    _img[x][positionCourante.y] = _skins[_menu->getIndexSkin()].getId(); // monkey

    // Fleche direction de saut
    if (_jeu->getJsonSerial()->joystickMaintenu(DROITE))
        _img[x + 1][15] = '>';
    else if (_jeu->getJsonSerial()->joystickMaintenu(GAUCHE))
        _img[x - 1][15] = '<';

    // Poussieres et eclats s'il attaque le serpent
    if (_jeu->getJsonSerial()->accShake()) {
        _img[x-1][14] = getCharEclat();
        _img[x]  [14] = getCharEclat();
        _img[x+1][14] = getCharEclat();
        _img[x-1][15] = getCharEclat();
        _img[x+1][15] = getCharEclat();
        _img[x-1][16] = getCharEclat();
        _img[x]  [16] = getCharEclat();
        _img[x+1][16] = getCharEclat();
    }
}

void AffichageConsole::afficherItems() {
    ElementJeu* elementCourant;
    for (int i = 0; i < _jeu->getElements().size(); i++) {
        elementCourant = _jeu->getElements()[i];

        // On affiche pas les objets hors jeu
        if (elementCourant->getPosition().y >= NB_LIGNES)
            continue;

        char visuel;
        switch (elementCourant->getID())
        {
        case OBSTACLE_FIXE:
            visuel = 'X';
            break;
        case HARPIE:
            visuel = '=';
            break;
        case SERPENT:
            visuel = 'S';
            break;
        case PIECE:
            visuel = '$';
            break;
        case BOUCLIER:
            visuel = '@';
            break;
        case BANANE:
            visuel = 'C';
            break;

        default:
            visuel = 'l';
        }

        _img[_xlianes[elementCourant->getPosition().x]][elementCourant->getPosition().y] = visuel;
    }
    
}

void AffichageConsole::afficherIU() {
    // Vider l'espace pour afficher le texte clairement
    for (int i = 1; i < NB_COLS - 1; i++) {
        _img[i][NB_LIGNES - 2] = ' ';
        _img[i][NB_LIGNES - 3] = '=';
    }

    // Afficher le texte pour le score
    _score = "Score : " + std::to_string(_jeu->getPointageJoueur()) + " Pieces : " + std::to_string(_jeu->getPiecesJoueur());
    afficherTexte(_score, 2, NB_LIGNES - 2);
}

void AffichageConsole::afficherGameOver() {
    afficherFichier("gameOver.txt", 3, 4);
    afficherFichier("retryText.txt", 7, 18);
}

void AffichageConsole::afficherPause() {
    int po = _jeu->getPauseOption();

    afficherFichier("pause.txt", 4, 4);
    afficherTexte("1. Continuer", 25, 13, (po == 0));
    afficherTexte("2. Retourner au menu", 21, 15, (po == 1));
}

void AffichageConsole::afficherContour() {
    // Coutour zone de jeu + UI
    for (int i = 0; i < NB_COLS; i++) {
        _img[i][0] = '-';
        _img[i][NB_LIGNES - 1] = '-';
    }
    for (int i = 1; i < NB_LIGNES - 1; i++) {
        _img[0][i] = '|';
        _img[NB_COLS - 1][i] = '|';
    }
}

void AffichageConsole::afficherTexte(std::string s, int x, int y, bool selected) {
    if (selected) {
        s = "> " + s + " <";
        x -= 2;
    }

    for (int i = 0; i < s.size() && x + i < NB_COLS; i++)
        _img[x + i][y] = s[i];
}

void AffichageConsole::afficherFichier(const char* nom, int x, int y) {
    std::ifstream fichier(nom);
    std::string texte;

    while (std::getline(fichier, texte) && y < NB_LIGNES)
        afficherTexte(texte, x, y++);
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
    // à la console d'un seul coup avec un seul appel de std::cout (very fast)
    _output.clear(); // Supprime le contenu de l'ancienne image dans la std::string
    std::cout << "\x1b[0;0H"; // Curseur position (0, 0) - ANSI escape sequence
    for (int y = 0; y < NB_LIGNES; y++) {
        for (int x = 0; x < NB_COLS; x++)
            _output += _img[x][y];
        _output += '\n';
    }
    std::cout << _output; // Imprime l'image à la console
}

char AffichageConsole::getCharEclat() {
    // 50% chance d'afficher un eclat, 50% d'afficher rien
    // * # @
    // 0 1 2 3 4 5
    switch (_rand.random(0, 5, rand())) {
        case 0: return '*';
        case 1: return '#';
        case 2: return '@';
    }
    return ' ';
}

bool AffichageConsole::peutAfficherProchaineImage() {
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastfrm);
    return elapsed.count() > _DURFRM; // S'assure que suffisamment de temps s'est écoulé depuis le dernier affichage (durée basée sur le FPS)
}

void AffichageConsole::attendreProchaineImage() {
    while (!peutAfficherProchaineImage()); // Attendre de pouvoir afficher la prochaine image
    _lastfrm = std::chrono::steady_clock::now(); // Update du temps de la dernière image
}
