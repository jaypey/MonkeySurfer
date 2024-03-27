#ifndef CMDCOLOR_H
#define CMDCOLOR_H

#include <string>

struct CMDColor {
    short r;
    short g;
    short b;

    bool operator==(CMDColor c) {
        return r == c.r && g == c.g && b == c.b;
    }

    bool operator!=(CMDColor c) {
        return r != c.r || g != c.g || b != c.b;
    }

    std::string to_string() {
        return "\x1b[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
    }
};

const extern CMDColor CMD_BOUCLIER_COLOR;
const extern CMDColor CMD_BANANE_COLOR;
const extern CMDColor CMD_CONTOUR_COLOR;
const extern CMDColor CMD_ECLAT_COLOR;
const extern CMDColor CMD_HARPIE_COLOR;
const extern CMDColor CMD_LIANE_COLOR;
const extern CMDColor CMD_MONKEY_COLOR;
const extern CMDColor CMD_OBSTACLE_COLOR;
const extern CMDColor CMD_PIECE_COLOR;
const extern CMDColor CMD_SERPENT_COLOR;
const extern CMDColor CMD_SKIN_BLOQUE_COLOR;
const extern CMDColor CMD_SKIN_SELECT_BLOQUE_COLOR;
const extern CMDColor CMD_WHITE;

#endif // CMDCOLOR_H!
