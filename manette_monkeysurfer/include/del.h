#ifndef DEL_H
#define DEL_H

#include <Arduino.h>

class Del
{
    public:
        Del();
        Del (int sapin);
        ~Del();
        void setpin(int sapin);
        int getpin();
        void instancier();
        void allumer();
        void eteindre();
        void clignoterrapidement();
        void clignoter();
        void clignoterlentement();

    private:
        int pin;

};

#endif

//rouge 23, jaune 25, vert 27, rouge1 22, rouge2 24, rouge3 26, jaune1 28
//jaune2 30, jaune3 32, jaune4 34, vert1 36, vert2 38, vert3 40
