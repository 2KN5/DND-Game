#include <stdio.h>
#include <stdlib.h>
#include "heroStats.h"

void heroStats(HeroData *heroes)
{
    heroes->score = 0;
    for(int i = 0; i < heroes->numberOfHeroes; i++)
    {
        if(heroes->data[i].class == 'B'){
            heroes->data[i].health = 8;
            heroes->data[i].numberOfMoves = 8;
        } else if(heroes->data[i].class == 'W'){
            heroes->data[i].health = 4;
            heroes->data[i].numberOfMoves = 10;
        } else if(heroes->data[i].class == 'E'){
            heroes->data[i].health = 6;
            heroes->data[i].numberOfMoves = 12;
        } else if(heroes->data[i].class == 'D'){
            heroes->data[i].health = 7;
            heroes->data[i].numberOfMoves = 6;
        } else if(heroes->data[i].class == 'H'){
            heroes->data[i].health = 12;
            heroes->data[i].numberOfMoves = 4;
        }
        heroes->data[i].actions[0] = 1;
        heroes->data[i].actions[1] = 1;
    }
}

void resetHeroes(HeroData *heroes){
    for(int i = 0; i < heroes->numberOfHeroes; ++i){
        heroes->data[i].actions[0] = 1;
        heroes->data[i].actions[1] = 1;
    }
}