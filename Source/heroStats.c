#include <stdio.h>
#include <stdlib.h>
#include "heroStats.h"

void heroStats(HeroData *hero)
{
    for(int i = 0; i < hero->numberOfHeroes; i++)
    {
        if(hero->data[i].class == 'B'){
            hero->data[i].health = 8;
            hero->data[i].numberOfMoves = 8;
        } else if(hero->data[i].class == 'W'){
            hero->data[i].health = 4;
            hero->data[i].numberOfMoves = 10;
        } else if(hero->data[i].class == 'E'){
            hero->data[i].health = 6;
            hero->data[i].numberOfMoves = 12;
        } else if(hero->data[i].class == 'D'){
            hero->data[i].health = 7;
            hero->data[i].numberOfMoves = 6;
        }
    }
}
