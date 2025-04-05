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

typedef struct Walls {
    int row;
    int column;
} Walls;

void genFurniture(char ***grid, int rows, int col);
void createGrid(char ***grid, int rows, int col);
int numberOfDig(int x);
void returnColChar(int x, int width);
void printGrid(char ***grid, int rows, int col, Hero hero[], Enemy enemy[], int partySize, int enemyCount, char *dif);
void freeGrid(char ***grid, int rows);

#endif