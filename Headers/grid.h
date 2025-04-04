#ifndef GRID_H
#define GRID_H

#include <stdio.h>
#include <stdlib.h>
#include "heroStats.h"

void createGrid(char ***grid, int rows, int col);
int numberOfDig(int x);
void printGrid(char ***grid, int rows, int col, struct Hero hero[], int partySize, char *dif);
void freeGrid(char ***grid, int rows);

#endif