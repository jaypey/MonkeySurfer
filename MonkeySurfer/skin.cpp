#include "skin.h"

Skin::Skin() : _id(' '), _prix(0), _debloque(false) {}

Skin::Skin(char id, const char *file) : _id(id), _file(file), _prix(0), _debloque(false) {}

Skin::~Skin() {}

void Skin::setId(char id) {
    _id = id;
}

void Skin::setFile(const char* file) {
    _file = file;
}

void Skin::setPrix(int prix) {
    _prix = prix;
}

void Skin::setDebloque(bool debloque) {
    _debloque = debloque;
}

char Skin::getId() {
    return _id;
}

const char *Skin::getFile() {
    return _file.c_str();
}

int Skin::getPrix() {
    return _prix;
}

bool Skin::isDebloque() {
    return _debloque;
}
