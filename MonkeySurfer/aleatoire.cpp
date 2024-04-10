#include <iostream>
#include <string>
#include "aleatoire.h"

/*Si aucun nouveau muon n'est d�tect� (la variable "muons" n'est ainsi pas incr�ment�), on cr�e une valeur semi-al�atoire 
de muons permettant un random plus uniforme (emp�che que la fonction random stagne et g�n�re la m�me valeur)*/
void RandomGenerator::verificateurNouveauMuon(int muons, int derniermuons)
{
    if (muons == derniermuons)
    {
        muons = (muons + muons) * (((muons) % 13) + 1);
    }
}

/*G�n�re un nombre random compris inclusivement entre la borne inf�rieure et sup�rieure selon la valeur de "muons" 
("muons" s'incr�mente avec le code Arduino reli� au Cosmic Watch mais aussi avec la fonction verificateurNouveauMuon 
si aucune nouveau muon n'est d�tect�)*/
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