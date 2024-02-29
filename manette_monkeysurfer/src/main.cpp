#include "jsonserial.h"

void setup() 
{
  Serial.begin(BAUD_RATE);
}

void loop() 
{
  // Creation des objets
  Accelerometre acc;
  Bargraph bar;
  Bouton btn(2, 3, 4, 5);
  Del delR(43);
  Del delJ(45);
  Del delV(47);
  Joystick joy(A4, A5);
  LiquidCrystal lcd(39, 37, 35, 33, 31, 29);
  MoteurVibrant motvib;

  // Configuration des objets
  bar.instancier(22, 24, 26, 28, 30, 32, 34, 36, 38, 40);
  delR.instancier();
  delJ.instancier();
  delV.instancier();

  // Configuration de l'objet "InfoComposantes"
  InfoComposantes info;
  info.acc = &acc;
  info.bar = &bar;
  info.btn = &btn;
  info.delR = &delR;
  info.delJ = &delJ;
  info.delV = &delV;
  info.joy = &joy;
  info.lcd = &lcd;
  info.motvib = &motvib;

  // Creation de l'objet JsonSerial
  JsonSerial js(&info);

  // Boucle de communication avec le PC
  while (true) {
    js.recvJson();
    js.sendJson();
  }
}
