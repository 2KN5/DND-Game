#ifndef GRID_H
#define GRID_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "heroStats.h"
#include "enemyStats.h"
#include "commonFunc.h"
#include "mainMenu.h"

#define WALL_CHANCE 7

typedef struct {
    int row;
    int column;
} Walls;

// Grid creation and initialization
void createSG(char ***grid, int rows, int col, HeroData *heroes, EnemyData *enemies, char dif[]);
void createGrid(char ***grid, int rows, int col, HeroData *heroes, EnemyData *enemies, char dif[]);
void clear_Rooms_Hallway(char ***grid, int rows, int col);

// Room and hallway generation
void createHallway(char ***grid, int rows, int col);
void createDoor(char ***grid, int currentRow, int upper, int lower);
void drawVertical_TOP(char ***grid, int rows, int col, Walls wall[], int *count);
void drawVertical_BOTTOM(char ***grid, int rows, int col, Walls wall[], int *count);
void drawHorizontal(char ***grid, int col, Walls wall[], int count);

// Room processing and labeling
void floodFillRoom(char **grid, int rows, int col, int ***roomMap, int x, int y, int roomID);
void countRooms(char **grid, int rows, int col, int ***roomMap, int *count);

// Room population
void genFurniture(char ***grid, int rows, int col);
void spawnHeroes(char ***grid, int rows, int col, HeroData *heroes);
void spawnEnemies(char ***grid, int rows, int col, EnemyData *enemies, int roomArea[rows * col][2], int count);
void populateRooms(char ***grid, int rows, int col, EnemyData *enemies, int **roomMap, int numberOfRooms, char dif[]);

// Grid display and memory
void printGrid(char ***grid, int rows, int col, HeroData heroes, EnemyData enemies, char dif[], int level);
void freeGrid(char ***grid, int rows);

// Column label utilities
int numberOfDig(int x);
void printColChar(int x, int width);
void getPositionChar(int x, int y, char pos[]);

#endif