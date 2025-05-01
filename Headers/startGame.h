#ifndef START_GAME_H
#define START_GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "grid.h"
#include "enemyMove.h"
#include "heroMove.h"
#include "enemyStats.h"
#include "heroStats.h"
#include "playerCommands.h"
#include "mainMenu.h"
#include "commonFunc.h"

// For the other commands
int otherCommands(char c, char ***grid, int rows, int col, HeroData *heroes, EnemyData enemies, char dif[], int level);

// Starting the game
void startGame(char ***grid, int rows, int col, HeroData *heroes, EnemyData *enemies, char dif[], int level);

#endif