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
    StaticJsonDocument<64> doc;
    
    Accelerometre accelerometre;
    Joystick joystick;
    Bouton bouton1;
    Bouton bouton2;
    Bouton bouton3;
    Bouton bouton4;

 
    int resultataccelerometre = accelerometre.shake('z');
    int resultatjoystick = joystick.;
    int resultatbouton1 = bouton1.;
    int resultatbouton2 = bouton2.;
    int resultatbouton3 = bouton3.;
    int resultatbouton4 = bouton4.;

    doc["shake"] = resultataccelerometre;
    doc["joystick"] = resultatjoystick;
    doc["bouton1"] = resultatbouton1;
    doc["bouton2"] = resultatbouton2;
    doc["bouton3"] = resultatbouton3;
    doc["bouton4"] = resultatbouton4;



    // Sérialisez l'objet JSON
    String jsonStr;
    serializeJson(doc, jsonStr);

    // Faire autre chose avec le résultat si nécessaire
    Serial.println(resultat);

    // Attendre un peu avant de recommencer
    delay(200);
}
