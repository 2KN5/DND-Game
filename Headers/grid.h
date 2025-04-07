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

int numberOfDig(int x);
int validString(char c[]);
void returnColChar(int x, int width);
void createGrid(char ***grid, Hero hero[], int partySize, Enemy enemy[], int numberOfE, int rows, int col);
void printGrid(char ***grid, int rows, int col, Hero hero[], Enemy enemy[], int partySize, int enemyCount, char *dif);
void freeGrid(char ***grid, int rows);

#endif