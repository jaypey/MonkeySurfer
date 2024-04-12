#ifndef SKIN_H
#define SKIN_H

#include <iostream>

class Skin {
public:
    Skin();
    Skin(std::string id, const char * file);
    ~Skin();

    void setId(std::string id);
    void setFile(const char* file);
    void setPrix(int prix);
    void setDebloque(bool debloque);
    std::string getId() const;
    const char *getFile() const;
    int getPrix() const;
    bool isDebloque() const;
private:
    std::string _id; // Caractere a afficher dans la console, aussi cle d'identification
    std::string _file; // Fichier de l'image du skin, pour affichage graphique Qt
    int _prix;
    bool _debloque;
};

#endif // !SKIN_H
