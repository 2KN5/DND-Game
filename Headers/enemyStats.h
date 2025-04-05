#ifndef ENEMY_STATS_H
#define ENEMY_STATS_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_MONSTER_COUNT 6

typedef struct Enemy {
    int numberOfMoves;
    int damage;
    int shields;
    int health;
    int x, y;
} Enemy;

void enemyStats(Enemy e[], char *dif, int *monsterCount);

#endif