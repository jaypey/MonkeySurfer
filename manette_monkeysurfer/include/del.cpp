#include "del.h"

        del::del()
        {
        }

        del::del (int sapin)
        {
            pin = sapin;
        }

        del::~del()
        {
        }
       
        void del::setpin(int sapin)
        {
            pin=sapin;
        }

        int del::getpin()
        {
            return pin;
        }

        void del::instancier()
        {
            pinMode(pin, OUTPUT);
        }

        void del::allumer()
        {
            digitalWrite(pin, HIGH);
        }

        void del::eteindre()
        {
            digitalWrite(pin, LOW);
        }

        void del::clignoterrapidement()
        {
            digitalWrite(pin, HIGH);
            delay(250);
            digitalWrite(pin, LOW);
            delay(250);
        }

        void del::clignoter()
        {
            digitalWrite(pin, HIGH);
            delay(500);
            digitalWrite(pin, LOW);
            delay(500);
        }

        void del::clignoterlentement()
        {
            digitalWrite(pin, HIGH);
            delay(1000);
            digitalWrite(pin, LOW);
            delay(1000);
        }
