#ifndef ACCELEROMETRE_H
#define ACCELEROMETRE_H
#define xPin A1
#define yPin A2
#define zPin A3

#include <Arduino.h>

class Accelerometre
{
  public: 
    int detection(char axe);
    bool shake(char axe);
}; 

#endif
