#include "json.h"


void Json::creationJsonVersPC()
{
    StaticJsonDocument<64> docverspc;

    Accelerometre accelerometre;
    /*Joystick joystick;
    Bouton bouton1;
    Bouton bouton2;
    Bouton bouton3;
    Bouton bouton4;*/

    int resultataccelerometre = accelerometre.shake('z');
    /*int resultatjoystick = joystick.;
    int resultatbouton1 = bouton1.;
    int resultatbouton2 = bouton2.;
    int resultatbouton3 = bouton3.;
    int resultatbouton4 = bouton4.;*/

    docverspc["shake"] = resultataccelerometre;
    /*docverspc["joystick"] = resultatjoystick;
    docverspc["bouton1"] = resultatbouton1;
    docverspc["bouton2"] = resultatbouton2;
    docverspc["bouton3"] = resultatbouton3;
    docverspc["bouton4"] = resultatbouton4;*/

    // Sérialiser l'objet JSON
    String jsonStr;
    serializeJson(doc, jsonStr);
    return;
}

void Json::recevoirJsonDuPC()
{
    if (Serial.available())
    {
        String data = Serial.readString();
        DynamicJsonDocument docversarduino(1024);
        DeserializationError error = deserializeJson(docversarduino, data);
        if (error)
        {
            Serial.println("Erreur lors du décodage JSON !");
            return;
        }

        LED1 = docversarduino["LED1"];
        LED2 = docversarduino["LED2"];
        LED3 = docversarduino["LED3"];
        Bargraph1 = docversarduino["Bargraph1"];
        Bargraph2 = docversarduino["Bargraph2"];
        Bargraph3 = docversarduino["Bargraph3"];
        Bargraph4 = docversarduino["Bargraph4"];
        Bargraph5 = docversarduino["Bargraph5"];
        Bargraph6 = docversarduino["Bargraph6"];
        Bargraph7 = docversarduino["Bargraph7"];
        Bargraph8 = docversarduino["Bargraph8"];
        Bargraph9 = docversarduino["Bargraph9"];
        Bargraph10 = docversarduino["Bargraph10"];
        LCD = docversarduino["LCD"];
        MoteurVibrant = docversarduino["MoteurVibrant"];

    }
}