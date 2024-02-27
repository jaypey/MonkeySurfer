#include <Arduino.h>
#include "del.h"
#include "del.cpp"
#include "bargraph.h"
#include "bargraph.cpp"
#include <LiquidCrystal.h>
#include <ArduinoJson.h>
#include "accelerometre.cpp"

JsonDocument doc;

del rouge(23);
del jaune(25);
del vert(27);
bargraph lebargraph;
LiquidCrystal ecran(39, 37, 35, 33, 31, 29);
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


void setup() 
{
  rouge.instancier();
  jaune.instancier();
  vert.instancier();
  lebargraph.instancier(22, 24, 26, 28, 30, 32, 34, 36, 38, 40);
  ecran.begin(16, 2);
  ecran.print("Vous etes mort!");
  Serial.begin(9600);
}

void loop() 
{
    StaticJsonDocument<64> docverspc;
    
    Accelerometre accelerometre;
    Joystick joystick;
    Bouton bouton1;
    Bouton bouton2;
    Bouton bouton3;
    Bouton bouton4;

 
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
  



    // Sérialisez l'objet JSON
    String jsonStr;
    serializeJson(doc, jsonStr);

    // Faire autre chose avec le résultat si nécessaire
    Serial.println(resultat);

    // Attendre un peu avant de recommencer
    delay(200);

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
