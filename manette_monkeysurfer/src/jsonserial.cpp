#include "jsonserial.h"

JsonSerial::JsonSerial(InfoComposantes* info) {
  _recvInProgress = false;
  _ndx = 0;
  _newData = false;
  _msg[0] = '\0';

  _lastsend = millis();

  _info = info;
}

JsonSerial::~JsonSerial() {}

void JsonSerial::recvJson() {
  recv();

  if (_newData == false)
    return;

  StaticJsonDocument<JSON_BUFFER_SIZE> doc;
  DeserializationError error = deserializeJson(doc, _msg);

  if (error) {
    _newData = false; // donnees invalides, on l'ecrase
    return;
  }

  // LED
  if (doc["delR"] == true) _info->delR->allumer(); else _info->delR->eteindre();
  if (doc["delJ"] == true) _info->delJ->allumer(); else _info->delJ->eteindre();
  if (doc["delV"] == true) _info->delV->allumer(); else _info->delV->eteindre();

  // BAR GRAPH

  int nbDeLumieres = doc["bar"];
  for (int i = 9; i >=0; i--){
    if (i < nbDeLumieres) {
      _info->bar->allumer(i);
    }
    else {
      _info->bar->eteindre(i);
    }
  }
  
  // LCD
  _info->lcd->begin(16, 2);
  _info->lcd->print((const char*) doc["lcd"][0]);
  _info->lcd->setCursor(0, 1);
  _info->lcd->print((const char*) doc["lcd"][1]);

  // MOTEUR VIBRANT
  if (doc["motvib"] == true) _info->motvib->controlerMoteur(HIGH); else _info->motvib->controlerMoteur(LOW);

  _newData = false;
}

void JsonSerial::sendJson() {
  // Delai d'envoi de JSON
  long long now = millis();
  long long elapsed = now - _lastsend;
  if (elapsed < SEND_DELAY)
    return;
  _lastsend = millis();

  StaticJsonDocument <JSON_BUFFER_SIZE> doc;

  // BOUTONS
  for (int i = 0; i < 4; i++) {
    BoutonState bstate = _info->btn->getState(i);
    doc["btn"][i]["appuye"] = bstate.appuye;
    doc["btn"][i]["maintenu"] = bstate.maintenu;
  }

  // ACCELEROMETRE
  doc["acc"] = _info->acc->shake('Z');

  // JOYSTICK
  JoystickState jstate = _info->joy->getStateX();
  doc["joyX"]["dir"] = (int) jstate.direction;
  doc["joyX"]["repeat"] = jstate.repetition;

  jstate = _info->joy->getStateY();
  doc["joyY"]["dir"] = (int) jstate.direction;
  doc["joyY"]["repeat"] = jstate.repetition;

  // ENVOI DU MESSAGE
  Serial.print(">");
  serializeJson(doc, Serial);
  Serial.print("<\n");
}

void JsonSerial::recv() {
  while (Serial.available() > 0 && _newData == false) {
    char c = Serial.read();

    if (_recvInProgress == true) {
      if (c != END_MARKER) {
        _msg[_ndx] = c;
        _ndx++;
        if (_ndx >= JSON_BUFFER_SIZE) {
          _ndx = JSON_BUFFER_SIZE - 1;
        }
      }
      else {
        _msg[_ndx] = '\0';
        _recvInProgress = false;
        _ndx = 0;
        _newData = true;
      }
    }
    else if (c == START_MARKER) {
      _recvInProgress = true;
    }
  }
}
