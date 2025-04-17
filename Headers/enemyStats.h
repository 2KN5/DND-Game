#ifndef ENEMY_STATS_H
#define ENEMY_STATS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int numberOfMoves;
    int health;
    int x, y;
    int isAlive;
} Enemy;

typedef struct {
    Enemy *data;
    int totalEnemies;
    int enemiesPerRoom;
} EnemyData;

// Single enemy spawn, for the M command
void spawnSingleEnemy(EnemyData *enemy, char dif[], int x, int y);

// Applying the enemy stats
void enemyStats(EnemyData *enemy, char dif[]);

#endif