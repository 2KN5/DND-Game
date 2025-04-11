#ifndef GRID_H
#define GRID_H

#include <stdio.h>
#include <stdlib.h>
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

int numberOfDig(int x);
void returnColChar(int x, int width);
void readMS(int *rows, int *col);
void genFurniture(char ***grid, int rows, int col, int **roomMap);
void createHallway(char ***grid, int rows, int col);
void createDoor(char ***grid, int currentRow, int upper, int lower);
void floodFillRoom(char **grid, int rows, int col, int ***roomMap, int x, int y, int roomID);
void countRooms(char **grid, int rows, int col, int ***roomMap, int *count);
void clear_Rooms_Hallway(char ***grid, int rows, int col);
void spawnHeroes(char ***grid, int rows, int col, HeroData *hero);
void spawnEnemies(char ***grid, int rows, int col, HeroData *hero, EnemyData *enemy, int roomArea[rows * col][2], int count);
void gen_Furniture_Enemies(char ***grid, int rows, int col, HeroData *hero, EnemyData *enemy, int **roomMap, int numberOfRooms, char dif[]);
void freeGrid(char ***grid, int rows);
void drawVertical_TOP(char ***grid, int rows, int col, Walls wall[], int *count);
void drawVertical_BOTTOM(char ***grid, int rows, int col, Walls wall[], int *count);
void drawHorizontal(char ***grid, int rows, int col, Walls wall[], int count);
void returnColChar(int x, int width);
void createGrid(char ***grid, int rows, int col, HeroData *hero, EnemyData *enemy, char dif[]);
void printGrid(char ***grid, int rows, int col, HeroData hero, EnemyData enemy, char dif[]);

#endif