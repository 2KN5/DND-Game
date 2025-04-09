#ifndef PLAYER_MOVEMENT_H
#define PLAYER_MOVEMENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "heroStats.h"
#include "enemyStats.h"
#include "commonFunc.h"

int checkString(char move[], int length, Hero hero[]);
int makeMove(char ***grid, int rows, int col, Hero hero[], Enemy enemy[]);

#endif