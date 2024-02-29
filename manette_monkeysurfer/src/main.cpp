#include <Arduino.h>
#include "del.h"
#include "bargraph.h"
#include "accelerometre.h"
#include <LiquidCrystal.h>
#include <ArduinoJson.h>
#include "bouton.h"
#include "moteurvibrant.h"
#include "joystick.h"

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
    /*StaticJsonDocument<64> doc;
    // Créer une instance de la classe Accelerometre
    Accelerometre pololo;

    // Appeler la fonction shake avec l'argument 'x'
    int resultat = pololo.shake('z');
    doc["shake"] = resultat;

    // Sérialisez l'objet JSON
    String jsonStr;
    serializeJson(doc, jsonStr);

    // Faire autre chose avec le résultat si nécessaire
    Serial.println(resultat);

    // Attendre un peu avant de recommencer
    delay(200);*/
  Joystick joystick;
  Bouton boutons;
  MoteurVibrant moteurVibrant;


}
