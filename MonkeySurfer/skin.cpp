#include "skin.h"

Skin::Skin() : _id(' ') {}

Skin::Skin(char id, const char *file) : _id(id), _file(file) {}

Skin::~Skin() {}

void Skin::setId(char id) {
    _id = id;
}

void Skin::setFile(const char* file) {
    _file = file;
}

char Skin::getId() {
    return _id;
}

const char *Skin::getFile() {
    return _file.c_str();
}