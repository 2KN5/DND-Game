#ifndef ENEMY_TURN_H
#define ENEMY_TURN_H

#include <stdio.h>
#include <stdlib.h>
#include "heroStats.h"
#include "enemyStats.h"
#include "enemyMove.h"

typedef struct {
    int x, y;
} Point;

int isValidTile(char **grid, int rows, int col, int targetX, int targetY, int visited[rows][col]);
void enemyTurn(char ***grid, int rows, int col, HeroData *heroes, EnemyData enemies);

#endif