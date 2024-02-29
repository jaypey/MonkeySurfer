#include "jsonserial.h"

JsonSerial::JsonSerial() {
  _recvInProgress = false;
  _ndx = 0;
  _newData = false;
  _msg[0] = '\0';
}

JsonSerial::~JsonSerial() {}

void JsonSerial::recvJson() {
  recv();

  if (_newData == false)
    return;

  StaticJsonDocument<64> doc;
  deserializeJson(doc, _msg);

  // LED

  // BAR GRAPH

  // LCD

  // MOTEUR VIBRANT
}

void JsonSerial::sendJson() {
  StaticJsonDocument<64> doc;

  // BOUTONS

  // ACCELEROMETRE
  
  // JOYSTICK

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
