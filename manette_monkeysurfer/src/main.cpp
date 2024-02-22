#include <ArduinoJson.h>
#include "accelerometre.cpp"

JsonDocument doc;

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
    StaticJsonDocument<64> doc;
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
    delay(200);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}