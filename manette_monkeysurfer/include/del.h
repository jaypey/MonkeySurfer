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
