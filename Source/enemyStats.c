#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "enemyStats.h"

void spawnSingleEnemy(EnemyData *enemy, char dif[], int x, int y){
    int lowerBound = 1, upperBound;
    if(strcmp(dif, "EASY") == 0){
        lowerBound = 1; upperBound = 3;
    } else if(strcmp(dif, "MEDIUM") == 0){
        lowerBound = 4; upperBound = 6;
    } else {
        lowerBound = 7; upperBound = 9;
    }
    int index = enemy->totalEnemies;
    enemy->data[index].health = rand() % (upperBound - lowerBound + 1) + lowerBound;
    enemy->data[index].numberOfMoves = 10;
    enemy->data[index].x = x; enemy->data[index].y = y; 
    enemy->data[index].isAlive = 1;
    ++(enemy->totalEnemies);
}

void enemyStats(EnemyData *enemy, char dif[]){
    int lowerBound = 1, upperBound;
    if(strcmp(dif, "EASY") == 0){
        enemy->enemiesPerRoom = rand() % 2 + 1;
        lowerBound = 1; upperBound = 3;
    } else if(strcmp(dif, "MEDIUM") == 0){
        enemy->enemiesPerRoom = rand() % 4 + 1;
        lowerBound = 4; upperBound = 6;
    } else {
        enemy->enemiesPerRoom = rand() % 6 + 1;
        lowerBound = 7; upperBound = 9;
    }
    for(int i = 0; i < enemy->enemiesPerRoom; i++){
        int index = enemy->totalEnemies + i;
        enemy->data[index].health = rand() % (upperBound - lowerBound + 1) + lowerBound;
        enemy->data[index].numberOfMoves = 10;
        enemy->data[index].isAlive = 1;
    }
}
