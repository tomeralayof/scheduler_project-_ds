#include <stdio.h>
#include "../include/bit_array.h"
#include "../include/knights_tour.h"


int solveKT(int idx,unsigned char[64]);

int main()
{
    unsigned char pos = 18;
    unsigned char tour[64] = {0};
    int i = 0;

    KnightsTour(pos,tour);

    for (i = 0; i < 64; i++)
    {
        printf("%d,",tour[i]);
    }
    
    return 0;
}