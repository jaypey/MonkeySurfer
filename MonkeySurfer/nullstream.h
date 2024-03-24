#ifndef NULLSTREAM_H
#define NULLSTREAM_H

#include <ostream>

class NullStream : public std::ostream {
public:
    NullStream() : std::ostream(nullptr) {}
    NullStream(const NullStream &) : std::ostream(nullptr) {}
};

template <class T>
const NullStream &operator<<(NullStream &&os, const T &value) {
    return os;
}

// Permet d'ignorer les messages d'erreur
extern NullStream null;

#endif // NULLSTREAM_H!
