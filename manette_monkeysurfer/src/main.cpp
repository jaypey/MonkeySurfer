#include <Arduino.h>
#include <ArduinoJson.h>

#define START_MARKER '>'
#define END_MARKER '<'
#define MAX_DATA_SIZE 1024

char data[MAX_DATA_SIZE];
int ndx = 0;
bool recvInProgress = false;
bool newData = false;

void recv();
void send();

void setup()
{
  Serial.begin(9600);
}

void loop() {
  recv();
  send();
}

void recv() {
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (recvInProgress == true) {
      if (rc != END_MARKER) {
        data[ndx] = rc;
        ndx++;
        if (ndx >= MAX_DATA_SIZE) {
          ndx = MAX_DATA_SIZE - 1;
        }
      }
      else {
        data[ndx] = '\0';
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }
    else if (rc == START_MARKER) {
      recvInProgress = true;
    }
  }
}

void send() {
  if (newData == false)
    return;

  StaticJsonDocument<500> doc;
  JsonVariant parse_msg;

  DeserializationError error = deserializeJson(doc, data);

  Serial.print("Received: ");
  Serial.println(data);

  if (error) {
    Serial.print("deserialize() failed: ");
    Serial.println(error.c_str());
  }
  else {
    Serial.println("Data received successfully");
  }

  newData = false;
}
