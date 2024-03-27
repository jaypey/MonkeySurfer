#include "del.h"

Del::Del()
{
}

Del::Del (int sapin)
{
    pin = sapin;
}

Del::~Del()
{
}

void Del::setpin(int sapin)
{
    pin=sapin;
}

int Del::getpin()
{
    return pin;
}

void Del::instancier()
{
    pinMode(pin, OUTPUT);
}

void Del::allumer()
{
    digitalWrite(pin, HIGH);
}

void Del::eteindre()
{
    digitalWrite(pin, LOW);
}

void Del::clignoterrapidement()
{
    digitalWrite(pin, HIGH);
    delay(250);
    digitalWrite(pin, LOW);
    delay(250);
}

void Del::clignoter()
{
    digitalWrite(pin, HIGH);
    delay(500);
    digitalWrite(pin, LOW);
    delay(500);
}

void Del::clignoterlentement()
{
    digitalWrite(pin, HIGH);
    delay(1000);
    digitalWrite(pin, LOW);
    delay(1000);
}
