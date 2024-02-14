#ifndef SKIN_H
#define SKIN_H

#include <iostream>

class Skin {
public:
    Skin(char, const char *);
    ~Skin();

    char getId();
    const char *getFile();
private:
    char _id; // Caract�re � afficher dans la console, aussi cl� d'identification
    std::string _file; // Fichier de l'image du skin, pour affichage graphique Qt
};

#endif // !SKIN_H
