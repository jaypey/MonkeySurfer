#include "accelerometre.h"

/*Retourne une valeur numérique concernant l'effet de la gravité sur l'axe entré en paramètre. Une valeur positive indique que
la manette se déplace dans la direction de l'axe tandis qu'une valeur négative dans la direction opposée. Plus la valeur est élevée, 
plus le déplacement est important*/
int Accelerometre::detection(char axe)
{
    int xMin = 267;
    int xMax = 400;
    int yMin = 264;
    int yMax = 400;
    int zMin = 275;
    int zMax = 403;
    const int samples = 10;

    if ((axe == 'X') || (axe == 'x'))
    {
        int xRaw=0;
        for(int i=0;i<samples;i++)
        {
            xRaw+=analogRead(xPin);
        }
        xRaw/=samples;

        int xMilliG = map(xRaw, xMin, xMax, -1000, 1000);

        return (xMilliG);
    }

    if ((axe == 'Y') || (axe == 'y'))
    {
       int yRaw=0;
        for(int i=0;i<samples;i++)
        {
            yRaw+=analogRead(yPin);
        }
        yRaw/=samples;

        int yMilliG = map(yRaw, yMin, yMax, -1000, 1000);

        return (yMilliG);
    }

    if ((axe == 'Z') || (axe == 'z'))
    {
        int zRaw=0;
        for(int i=0;i<samples;i++)
        {
            zRaw+=analogRead(zPin);
        }
        zRaw/=samples;

        int zMilliG = map(zRaw, zMin, zMax, -1000, 1000);
  
        return (zMilliG);
    }
}

//Vérifie si un secouement sur l'axe entré en paramètre a lieu. Retourne true si secouement, false sinon.
bool Accelerometre::shake(char axe)
{
    if ((axe == 'X') || (axe == 'x'))
    {
        if ((detection('x') > 300 )|| (detection('x') < -400))
        {
            return false;
        }
        else
        {
            return true;
        }
    }
     if ((axe == 'Y') || (axe == 'y'))
    {
        
        if ((detection('y') > 200)|| (detection('y') < 200))
        {
            return false;
        }
        else
        {
            return true;
        }
    }
     if ((axe == 'Z') || (axe == 'z'))
    {
        
        if ((detection('z') > 1700)|| (detection('z') < 500))
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}
