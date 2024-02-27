#include <Arduino.h>
#include "del.h"
#include "del.cpp"
#include "bargraph.h"
#include "bargraph.cpp"
#include <LiquidCrystal.h>
//rouge 23, jaune 25, vert 27, rouge1 22, rouge2 24, rouge3 26, jaune1 28, jaune2 30, jaune3 32, jaune4 34, vert1 36, vert2 38, vert3 40

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
}

void loop() 
{
  lebargraph.joie();
  rouge.allumer();
  jaune.allumer();
  vert.allumer();
}
