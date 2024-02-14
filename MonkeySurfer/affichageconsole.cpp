#include "affichageconsole.h"

AffichageConsole::AffichageConsole(Jeu *j) : Affichage(j) {
    _lastfrm = std::chrono::steady_clock::now();
    afficherArrierePlan();

    // Positionnement des lianes, centré dans la zone de jeu
    int milieu = NB_COLS / 2;
    for (int i = 0; i < NB_LIANES; i++) {
        int multiple_offset = i - (NB_LIANES / 2);
        _xlianes[i] = milieu + (ECART_LIANES * multiple_offset);
    }
}

AffichageConsole::~AffichageConsole() {}

void AffichageConsole::afficher() {
    while (!peutAfficherProchaineImage()); // Attendre de pouvoir afficher la prochaine image
    _lastfrm = std::chrono::steady_clock::now(); // Update du temps de la dernière image

    // Remplissage des informations dans la matrice de char
    afficherArrierePlan();
    afficherLianes();
    afficherJoueur();
    afficherItems();
    afficherObstacles();
    afficherIU();

    // Transposition des informations de la matrice de char dans une seule std::string pour tout imprimer
    // à la console d'un seul coup avec un seul appel de std::cout (very fast)
    _output.clear(); // Supprime le contenu de l'ancienne image
    std::cout << "\x1b[0;0H"; // Curseur position (0, 0) - ANSI escape sequence
    for (int y = 0; y < NB_LIGNES; y++) {
        for (int x = 0; x < NB_COLS; x++)
            _output += _img[x][y];
        _output += '\n';
    }
    std::cout << _output; // Imprime l'image à la console
}

void AffichageConsole::afficherArrierePlan() {
    for (int y = 0; y < NB_LIGNES; y++)
        for (int x = 0; x < NB_COLS; x++)
            _img[x][y] = ' ';
}

void AffichageConsole::afficherLianes() {
    for (int i = 0; i < NB_LIANES; i++)
        for (int y = 0; y < NB_LIGNES; y++)
            _img[_xlianes[i]][y] = 'l';
}

void AffichageConsole::afficherJoueur() {
    // Test - à faire pour de vrai plus tard
    static int x = _xlianes[0];
    static int d = 1;
    _img[x][15] = 'M'; // monkey
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
    // Coutour zone de jeu + UI
    for (int i = 0; i < NB_COLS; i++) {
        _img[i][0] = '-';
        _img[i][NB_LIGNES - 3] = '-';
        _img[i][NB_LIGNES - 1] = '-';
    }
    for (int i = 1; i < NB_LIGNES - 1; i++) {
        _img[0][i] = '|';
        _img[NB_COLS - 1][i] = '|';
    }

    // Vider l'espace pour afficher le texte clairement
    for (int i = 1; i < NB_COLS - 1; i++)
        _img[i][NB_LIGNES - 2] = ' ';

    // Afficher le texte pour le score
    _score = "Score : " + std::to_string(28 /*_jeu->getScore()*/);
    for (int i = 0; i < _score.size(); i++)
        _img[i + 2][NB_LIGNES - 2] = _score[i];
}

bool AffichageConsole::peutAfficherProchaineImage() {
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastfrm);
    return elapsed.count() > _DURFRM; // S'assure que suffisamment de temps s'est écoulé depuis le dernier affichage (durée basée sur le FPS)
}
