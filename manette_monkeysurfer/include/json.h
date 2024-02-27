#ifndef JSON_H
#define JSON_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "accelerometre.cpp"

class Json
{
public:
    int LED1 = 0;
    int LED2 = 0;
    int LED3 = 0;
    int Bargraph1 = 0;
    int Bargraph2 = 0;
    int Bargraph3 = 0;
    int Bargraph4 = 0;
    int Bargraph5 = 0;
    int Bargraph6 = 0;
    int Bargraph7 = 0;
    int Bargraph8 = 0;
    int Bargraph9 = 0;
    int Bargraph10 = 0;
    int MoteurVibrant = 0;
    char* LCD = "";
    void creationJsonVersPC();
    void recevoirJsonDuPC();
};

#endif
