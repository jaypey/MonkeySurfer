#ifndef COORDONNEE_H
#define COORDONNEE_H

struct Coordonnee {
    int x;
    int y;

    bool operator==(const Coordonnee& other) const {
        return (x == other.x) && (y == other.y);
    }
};



#endif //COORDONNEE_H

