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

// Pathfinding for the enemies
int isValidTile(char **grid, int rows, int col, int x, int y, int visited[rows][col]);
int findPath(char **grid, int rows, int col, int enemyX, int enemyY, int heroX, int heroY, int *pathLength, Point path[]);

// Enemy turn
void enemyTurn(char ***grid, int rows, int col, HeroData *heroes, EnemyData enemies);

#endif