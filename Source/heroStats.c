#include <stdio.h>
#include <stdlib.h>
#include "heroStats.h"

void stats(Hero h[], int count)
{
    for(int i = 0; i < count; i++)
    {
        if(h[i].class == 'B')
        {
            h[i].health = 8;
            h[i].numberOfMoves = 8;
        }
        if(h[i].class == 'W')
        {
            h[i].health = 4;
            h[i].numberOfMoves = 10;
        }
        if(h[i].class == 'E')
        {
            h[i].health = 6;
            h[i].numberOfMoves = 12;
        }
        if(h[i].class == 'D')
        {
            h[i].health = 7;
            h[i].numberOfMoves = 6;
        }
    }
}
