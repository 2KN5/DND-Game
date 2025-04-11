#ifndef PLAYER_COMMANDS_H
#define PLAYER_COMMANDS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "heroStats.h"
#include "enemyStats.h"
#include "commonFunc.h"

int checkValidMoves(char moves[], int length);
int checkAttack(char attack[], int length);
int isHero(char c, HeroData heroes);
int checkValidLetters(char move[], int length, HeroData heroes);
int checkString(char str[], int length, HeroData heroes);
char checkMove(char ***grid, int rows, int col, HeroData heroes, EnemyData enemies);
void applyMove(char ***grid, int rows, int col, HeroData *heroes, EnemyData *enemies, char move);

#endif