#include "skin.h"

Skin::Skin() : _id(" "), _prix(0), _debloque(false) {}

Skin::Skin(std::string id, const char *file) : _id(""), _file(file), _prix(0), _debloque(false) {}

Skin::~Skin() {}

void Skin::setId(std::string id) {
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

std::string Skin::getId() const {
    return _id;
}

const char *Skin::getFile() const {
    return _file.c_str();
}

int Skin::getPrix() const{
    return _prix;
}

bool Skin::isDebloque() const {
    return _debloque;
}
