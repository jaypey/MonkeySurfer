#include "muons.h"
int DetecteurMuons::detecteurDeMuons()
{
  int valeur = analogRead(A0);
  if (valeur > 290)
  {
    muons ++;
    //Serial.println(muons);
  }
  return muons;
}