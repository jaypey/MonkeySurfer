#include <iostream>
#include "aleatoire.h"

int main()
{
    RandomGenerator randomnbr;
    for (int i=0; i<100; i++)
    {
        std::cout << randomnbr.random(10, 45, 1545652657) << std::endl;
    }


}
