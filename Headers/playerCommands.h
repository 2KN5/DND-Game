#ifndef PLAYER_COMMANDS_H
#define PLAYER_COMMANDS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "grid.h"
#include "heroStats.h"
#include "enemyStats.h"
#include "heroMove.h"
#include "enemyMove.h"
#include "commonFunc.h"

// Attack and targeting
int canAttack(char ***grid, int rows, int col, int x, int y, HeroData heroes, char move[], int heroIndex);
int checkAttack(char attack[], int length);

// Enemy management
void cdEnemy(char ***grid, int rows, int col, EnemyData *enemies, char dif[], int x, int y, char pos[]);
int getEnemyIndex(EnemyData enemies, int x, int y);
void shiftEnemies(EnemyData *enemies, int index);

// Hero and input management
int applyCommand(char ***grid, int rows, int col, HeroData *heroes, EnemyData *enemies, char dif[], char command, char move[]);
int applyMove(char ***grid, int rows, int col, char moves[], int length, Hero *hero);
int checkHealerMove(Hero hero, char move[]);
char checkMove(char ***grid, int rows, int col, HeroData heroes, EnemyData enemies, char move[]);
int getCoords(char str[], int index, int rows, int col, int *x, int *y, char pos[]);
int getHeroIndex(HeroData heroes, char hero);
int isHero(char c, HeroData heroes);
int otherCommands(char c, char ***grid, int rows, int col, HeroData *heroes, EnemyData enemies, char dif[], int level);
int playerActions(HeroData *heroes);
int validCell(HeroData heroes, int x, int y, int index);

// String parsing
int checkString(char str[], int length, HeroData heroes);
int checkValidLetters(char command[], int length, HeroData heroes);
int checkValidMoves(char moves[], int length, Hero hero);
int returnColNumber(char letters[]);
void updatePositionChar(int x, int y, char pos[]);

#endif
