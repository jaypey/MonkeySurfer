#include "affichageconsole.h"

AffichageConsole::AffichageConsole(Jeu *j) : Affichage(j) {
    _lastfrm = std::chrono::steady_clock::now();
    initialiserLianes();
    initialiserSkins();
    afficherArrierePlan();
}

AffichageConsole::~AffichageConsole() {}

void AffichageConsole::afficherJeu() {
    attendreProchaineImage();

    // Remplissage des informations dans la matrice de char
    afficherArrierePlan();
    afficherLianes();
    afficherJoueur();
    afficherItems();
    afficherObstacles();
    afficherContour();
    afficherIU();
    afficherGameOver();

    // Print � la console
    printMatriceChar();
}

void AffichageConsole::afficherMenu() {
    attendreProchaineImage();

    // Remplissage des informations dans la matrice de char
    afficherArrierePlan();
    afficherContour();
    afficherFichier("artMenu.txt", 5, 2);
    afficherFichier("monkey.txt", 43, 4);
    afficherTexte("1. Jouer", 25, 15);
    afficherTexte("2. Skins", 25, 17);
    afficherTexte("3. Aide", 25, 19);
    afficherTexte("4. Quitter", 25, 21);

    // Print � la console
    printMatriceChar();
}

void AffichageConsole::afficherMenuSkin() {
    attendreProchaineImage();

    // Remplissage des informations dans la matrice de char
    afficherArrierePlan();
    afficherContour();

    // Affichage de la shop
    for (int rangee = 0; rangee < 3; rangee++)
        for (int col = 0; col < 3; col++) {
            int index = col + rangee * 3;

            std::string apparence;
            apparence += _skins[index].getId();

            const char* fichier = (_indexSkin == index)
                                ? "showcaseSkinSelect.txt"
                                : "showcaseSkin.txt";
            afficherFichier(fichier, 8 + col * ECART_COL_SKINS, 2 + rangee * ECART_RANGEE_SKINS);
            afficherTexte(apparence, 12 + col * ECART_COL_SKINS, 4 + rangee * ECART_RANGEE_SKINS);
        }

    std::string apparenceCourante = "Skin choisi : ";
    apparenceCourante += _skins[_indexSkin].getId();
    afficherTexte(apparenceCourante, 22, 20);

    afficherTexte("Appuyer sur les fleches pour choisir un skin", 7, 21);
    afficherTexte("Appuyer sur 'q' pour quitter", 15, 22);

    // Print � la console
    printMatriceChar();
}

void AffichageConsole::afficherAide() {
    attendreProchaineImage();

    // Remplissage des informations dans la matrice de char
    afficherArrierePlan();
    afficherContour();

    // Affichage du tutoriel
    std::string explicationSinge = " : Represente le singe (le joueur).";
    explicationSinge.insert(explicationSinge.begin(), _skins[_indexSkin].getId());

    afficherTexte(explicationSinge, 3, 3);

    afficherTexte("# : Les obstacles, le singe doit les eviter!", 3, 5);

    afficherTexte("B : Les bananes, ramassez les pour accumuler des points!", 3, 7);

    afficherTexte("Appuyer sur les fleches pour sauter de liane en liane.", 3, 9);

    afficherTexte("Une apparence differente peut etre choisie pour le singe", 3, 11);
    afficherTexte("dans le menu de skins, accessible par le menu principal.", 3, 12);

    afficherTexte("Appuyer sur 'q' pour revenir au menu.", 12, 21);

    // Print � la console
    printMatriceChar();
}

void AffichageConsole::afficherLoading() {
    // Gros monkey qui bondit sur l'�cran
    // Le code ci-dessous simule un monkey avec des physiques
    // qui bondit de gauche � droite & vice-versa, avec velocite
    // et vitesse pour d�terminer la vitesse de chute

    attendreProchaineImage();

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
    afficherFichier("monkey.txt", posX, posY);
    afficherTexte("Chargement...", 25, 2);

    printMatriceChar();
}

void AffichageConsole::modifierSkin(int val) {
    _indexSkin = (_indexSkin + val) % NB_SKINS;
    if (_indexSkin < 0) _indexSkin += NB_SKINS;
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
    // Test - � faire pour de vrai plus tard
    static int x = _xlianes[0];
    static int d = 1;
    _img[x][15] = _skins[_indexSkin].getId(); // monkey
    x += d;
    if (x == _xlianes[NB_LIANES - 1])
        d = -1;
    if (x == _xlianes[0])
        d = 1;
}

void AffichageConsole::afficherItems() {
    /* PSEUDO-CODE
    for (int i = 0; i < _jeu->items().taille(); i++)
        _img[_jeu->items()[i].x()][_jeu->items()[i].y()];
    */
}

void AffichageConsole::afficherObstacles() {
    /* PSEUDO-CODE
    for (int i = 0; i < _jeu->obstacles().taille(); i++)
        _img[_jeu->obstacles()[i].x()][_jeu->obstacles()[i].y()];
    */
}

void AffichageConsole::afficherIU() {
    // Vider l'espace pour afficher le texte clairement
    for (int i = 1; i < NB_COLS - 1; i++) {
        _img[i][NB_LIGNES - 2] = ' ';
        _img[i][NB_LIGNES - 3] = '=';
    }

    // Afficher le texte pour le score
    _score = "Score : " + std::to_string(28 /*_jeu->getScore()*/);
    afficherTexte(_score, 2, NB_LIGNES - 2);
}

void AffichageConsole::afficherGameOver() {
    afficherFichier("gameOver.txt", 3, 4);
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

void AffichageConsole::afficherTexte(const std::string& s, int x, int y) {
    for (int i = 0; i < s.size() && x + i < NB_COLS; i++)
        _img[x + i][y] = s[i];
}

void AffichageConsole::afficherFichier(const char* nom, int x, int y) {
    std::ifstream fichier(nom);
    std::string texte;

    while (std::getline(fichier, texte) && y < NB_LIGNES)
        afficherTexte(texte, x, y++);
}

void AffichageConsole::printMatriceChar() {
    // Transposition des informations de la matrice de char dans une seule std::string pour tout imprimer
    // � la console d'un seul coup avec un seul appel de std::cout (very fast)
    _output.clear(); // Supprime le contenu de l'ancienne image dans la std::string
    std::cout << "\x1b[0;0H"; // Curseur position (0, 0) - ANSI escape sequence
    for (int y = 0; y < NB_LIGNES; y++) {
        for (int x = 0; x < NB_COLS; x++)
            _output += _img[x][y];
        _output += '\n';
    }
    std::cout << _output; // Imprime l'image � la console
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
