#ifndef PLAYER_COMMANDS_H
#define PLAYER_COMMANDS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "heroStats.h"
#include "enemyStats.h"
#include "heroMove.h"
#include "enemyMove.h"
#include "commonFunc.h"

// Movement and input
char checkMove(char ***grid, int rows, int col, HeroData heroes, EnemyData enemies, char move[]);
int applyCommand(char ***grid, int rows, int col, HeroData *heroes, EnemyData *enemies, char dif[], char command, char move[]);

// String and position parsing
int checkValidMoves(char moves[], int length, Hero hero);
int checkAttack(char attack[], int length);
int isHero(char c, HeroData heroes);
int checkValidLetters(char command[], int length, HeroData heroes);
int checkString(char str[], int length, HeroData heroes);
int returnColNumber(char letters[]);
int getCoords(char str[], int index, int rows, int col, int *x, int *y, char pos[]);

// Enemy and hero mechanics
int otherCommands(char c, char ***grid, int rows, int col, HeroData *heroes, EnemyData enemies, char dif[], int level);
void playerActions(HeroData *heroes);
void shiftEnemies(EnemyData *enemies, int index);
void cdEnemy(char ***grid, int rows, int col, EnemyData *enemies, char dif[], int x, int y, char pos[]);
int validCell(HeroData heroes, int x, int y, int index);
int canAttack(char ***grid, int rows, int col, int x, int y, HeroData heroes, char move[], int heroIndex);
int getHeroIndex(HeroData heroes, char hero);
int getEnemyIndex(EnemyData enemies, int x, int y);

#endif