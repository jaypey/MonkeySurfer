#ifndef SKIN_H
#define SKIN_H

#include <iostream>

class Skin {
public:
    Skin();
    Skin(char id, const char * file);
    ~Skin();

    void setId(char id);
    void setFile(const char* file);
    void setPrix(int prix);
    void setDebloque(bool debloque);
    char getId();
    const char *getFile();
    int getPrix();
    bool isDebloque();
private:
    char _id; // Caractere a afficher dans la console, aussi cle d'identification
    std::string _file; // Fichier de l'image du skin, pour affichage graphique Qt
    int _prix;
    bool _debloque;
};

#endif // !SKIN_H
