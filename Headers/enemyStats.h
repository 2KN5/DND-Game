#ifndef ENEMY_STATS_H
#define ENEMY_STATS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int numberOfMoves;
    int damage;
    int shields;
    int health;
    int x, y;
} Enemy;

void enemyStats(Enemy e[], char *dif, int *monsterCount);

#endif