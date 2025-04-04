#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "enemyStats.h"

void enemyStats(struct Enemy e[], char *dif)
{
    if(strcmp(dif, "EASY\n") == 0)
    {
        int enemynumber = rand() % 2 + 1;
        for(int i = 0; i < enemynumber; i++)
        {
            e[i].health = rand() % 3 + 1;
            e[i].numberOfMoves = 10;
        }
    }
    if(strcmp(dif, "MEDIUM\n") == 0)
    {
        int enemynumber = rand() % 3 + 2;
        for( int i = 0; i < enemynumber; i++)
        {
            e[i].health = rand() % 3 + 4;
            e[i].numberOfMoves = 10;
        }
    }
    if(strcmp(dif, "HARD\n") == 0)
    {
        int enemynumber=rand() % 3 + 4;
        for( int i = 0; i < enemynumber; i++)
        {
            e[i].health = rand() % 3 + 7;
            e[i].numberOfMoves = 10;
        }
    }
}