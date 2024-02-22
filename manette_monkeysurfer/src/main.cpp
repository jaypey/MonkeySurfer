#include "accelerometre.cpp"

// put function declarations here:
int myFunction(int, int);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
    // Créer une instance de la classe Accelerometre
    Accelerometre pololo;

    // Appeler la fonction shake avec l'argument 'x'
    int resultat = pololo.shake('z');

    // Faire autre chose avec le résultat si nécessaire
    Serial.println(resultat);
    //pololo.detection('z');
    //Serial.println(pololo.detection('z'));
    

    // Attendre un peu avant de recommencer
    delay(200);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}