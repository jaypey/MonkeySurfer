#ifndef BARGRAPH_H
#define BARGRAPH_H

#include "del.h"
#include <Arduino.h>

class Bargraph
{
    public:
        Bargraph();
        ~Bargraph();
        void instancier(int del1, int del2, int del3, int del4, int del5, int del6, int del7, int del8, int del9, int del10);
        void allumer();
        void eteindre();
        void joie();
    
    private:
        Del dels[10];
};


#endif