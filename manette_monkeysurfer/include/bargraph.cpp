#include "bargraph.h"

        bargraph::bargraph()
        {
        }

        bargraph::~bargraph()
        {
        }

        void bargraph::instancier(int del1, int del2, int del3, int del4, int del5, int del6, int del7, int del8, int del9, int del10)
        {
            dels[0].setpin(del1);
            dels[1].setpin(del2);
            dels[2].setpin(del3);
            dels[3].setpin(del4);
            dels[4].setpin(del5);
            dels[5].setpin(del6);
            dels[6].setpin(del7);
            dels[7].setpin(del8);
            dels[8].setpin(del9);
            dels[9].setpin(del10);
            for (int i=0; i<10; i++)
            {
                pinMode(dels[i].getpin(), OUTPUT);
            }
        }

        void bargraph::allumer()
        {
            for (int i=0; i<10; i++)
            {
                digitalWrite(dels[i].getpin(), HIGH);
            }
        }

        void bargraph::eteindre()
        {
            for (int i=0; i<10; i++)
            {
                digitalWrite(dels[i].getpin(), LOW);
            }
        }
        
        void bargraph::joie()
        {
            for (int i=0; i<10; i++)
            {
                digitalWrite(dels[i].getpin(), HIGH);
                delay(100);
            }
             for (int i=0; i<10; i++)
            {
                digitalWrite(dels[i].getpin(), LOW);
                delay(100);
            }
        }