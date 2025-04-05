#ifndef GRID_H
#define GRID_H

#include <stdio.h>
#include <stdlib.h>
#include "heroStats.h"
#include "enemyStats.h"
#include "clearScreen.h"

void createGrid(char ***grid, int rows, int col);
int numberOfDig(int x);
void returnColChar(int x, int width);
void printGrid(char ***grid, int rows, int col, struct Hero hero[], struct Enemy enemy[], int partySize, int enemyCount, char *dif);
void freeGrid(char ***grid, int rows);

#endif