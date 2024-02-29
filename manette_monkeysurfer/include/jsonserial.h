#ifndef JSONSERIAL_H
#define JSONSERIAL_H

#include <Arduino.h>
#include <ArduinoJson.h>

#define START_MARKER '>'
#define END_MARKER '<'
#define JSON_BUFFER_SIZE 1024

struct InfoComposantes {

};

class JsonSerial {
public:
  JsonSerial();
  ~JsonSerial();

  void recvJson();
  void sendJson();

private:
  void recv();

  bool _recvInProgress;
  int _ndx;
  bool _newData;
  char _msg[JSON_BUFFER_SIZE];
};

#endif // JSONSERIAL_H!
