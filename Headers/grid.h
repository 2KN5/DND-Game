#ifndef GRID_H
#define GRID_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "heroStats.h"
#include "enemyStats.h"
#include "clearScreen.h"

#define WALL_CHANCE 7

typedef struct {
    int row;
    int column;
} Walls;

void returnColChar(int x, int width);
int numberOfDig(int x);
void genFurniture(char ***grid, int rows, int col, int **roomMap);
void createHallway(char ***grid, int rows, int col);
void createDoor(char ***grid, int currentRow, int upper, int lower);
void floodFillRoom(char **grid, int rows, int col, int ***roomMap, int x, int y, int roomID);
void countRooms(char **grid, int rows, int col, int ***roomMap, int *count);
void clear_Rooms_Hallway(char ***grid, int rows, int col);
void spawnHeroes(char ***grid, Hero hero[], int numberOfHeroes, int rows, int col);
void spawnEnemies(char ***grid, Enemy enemy[], int numberOfEnemies, int rows, int col, int roomArea[rows * col][2], int count);
void gen_Furniture_Enemies(char ***grid, Enemy enemy[], int rows, int col, int **roomMap, int numberOfRooms, char dif[]);
void freeGrid(char ***grid, int rows);
void drawVertical_TOP(char ***grid, Walls wall[], int rows, int col, int *count);
void drawVertical_BOTTOM(char ***grid, Walls wall[], int rows, int col, int *count);
void drawHorizontal(char ***grid, Walls wall[], int rows, int col, int count);
int validString(char c[]);
void returnColChar(int x, int width);
void createGrid(char ***grid, Hero hero[], int partySize, Enemy enemy[], char dif[], int rows, int col);
void printGrid(char ***grid, Hero hero[], int partySize, Enemy enemy[], char *dif, int rows, int col);

#endif