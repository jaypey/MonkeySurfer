#include <iostream>
#include <string>
#include "aleatoire.h"

/*Si aucun nouveau muon n'est détecté (la variable "muons" n'est ainsi pas incrémenté), on crée une valeur semi-aléatoire 
de muons permettant un random plus uniforme (empêche que la fonction random stagne et génère la même valeur)*/
void RandomGenerator::verificateurNouveauMuon(int muons, int derniermuons)
{
    if (muons == derniermuons)
    {
        muons = (muons + muons) * (((muons) % 13) + 1);
    }
}

/*Génère un nombre random compris inclusivement entre la borne inférieure et supérieure selon la valeur de "muons" 
("muons" s'incrémente avec le code Arduino relié au Cosmic Watch mais aussi avec la fonction verificateurNouveauMuon 
si aucune nouveau muon n'est détecté)*/
int RandomGenerator::random(int borneinf, int bornesup, int muons)
{
    int nbr;
    int modulo = abs(bornesup - borneinf);
    if (borneinf>bornesup)
    {
        int a = bornesup;
        bornesup = borneinf;
        borneinf = a;
    }
    nbr = (muons % (modulo+1))+borneinf;

    return nbr;
}