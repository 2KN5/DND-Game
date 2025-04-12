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

typedef struct {
    Enemy *data;
    int totalEnemies;
    int enemiesPerRoom;
} EnemyData;

void enemyStats(EnemyData *enemy, char dif[]);
void spawnSingleEnemy(EnemyData *enemy, char dif[], int x, int y);

#endif