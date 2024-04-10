#include "muons.h"
int DetecteurMuons::detecteurDeMuons()
{
  int valeur = analogRead(A0);
  if (valeur > 320)
  {
    muons ++;
    //Serial.println(muons);
  }
  return muons;
}