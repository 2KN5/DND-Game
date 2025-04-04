#ifndef ENEMY_STATS_H
#define ENEMY_STATS_H

#include <stdio.h>
#include <stdlib.h>

struct Enemy {
    int numberOfMoves;
    int damage;
    int shields;
    int health;
    int x, y;
};

void enemyStats(struct Enemy e[], char *dif);

#endif