#ifndef JSONSERIAL_H
#define JSONSERIAL_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <LiquidCrystal.h>
#include "accelerometre.h"
#include "bargraph.h"
#include "bouton.h"
#include "del.h"
#include "joystick.h"
#include "moteurvibrant.h"
#include "muons.h"

#define BAUD_RATE 112500
#define START_MARKER '>'
#define END_MARKER '<'
#define JSON_BUFFER_SIZE 1024
#define SEND_DELAY 50

struct InfoComposantes {
  Accelerometre* acc;
  Bargraph* bar;
  Bouton* btn;
  Del* delR;
  Del* delJ;
  Del* delV;
  Joystick* joy;
  LiquidCrystal* lcd;
  MoteurVibrant* motvib;
  DetecteurMuons* muons;
};

class JsonSerial {
public:
  JsonSerial(InfoComposantes* info);
  ~JsonSerial();

  void recvJson();
  void sendJson();

private:
  void recv();

  bool _recvInProgress;
  int _ndx;
  bool _newData;
  char _msg[JSON_BUFFER_SIZE];

  long long _lastsend;

  InfoComposantes* _info;
};

#endif // JSONSERIAL_H!
