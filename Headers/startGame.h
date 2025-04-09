#ifndef START_GAME_H
#define START_GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "grid.h"
#include "enemyDamage.h"
#include "enemyStats.h"
#include "heroDamage.h"
#include "heroStats.h"
#include "playerMovement.h"
#include "mainMenu.h"
#include "commonFunc.h"

void startGame(char ***grid, Hero hero[], Enemy enemy[], char dif[], int rows, int col);

#endif