#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "enemyStats.h"

void enemyStats(Enemy e[], char *dif, int *monsterCount){

    int lowerBound, upperBound;
    if(strcmp(dif, "EASY") == 0){
        *monsterCount = rand() % 2 + 1;
        lowerBound = 1; upperBound = 3;
    } else if(strcmp(dif, "MEDIUM") == 0){
        *monsterCount = rand() % 2 + 3;
        lowerBound = 4; upperBound = 6;
    } else {
        *monsterCount = rand() % 2 + 5;
        lowerBound = 7; upperBound = 9;
    }
    for(int i = 0; i < *monsterCount; i++){
        e[i].health = rand() % (upperBound - lowerBound + 1) + lowerBound;
        e[i].numberOfMoves = 10;
    }
}