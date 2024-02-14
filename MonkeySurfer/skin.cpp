#include "skin.h"

Skin::Skin(char c, const char *f) : _id(c), _file(f) {}

Skin::~Skin() {}

char Skin::getId() {
    return _id;
}

const char *Skin::getFile() {
    return _file.c_str();
}
