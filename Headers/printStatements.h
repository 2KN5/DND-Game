#ifndef PRINT_STATEMENTS_H
#define PRINT_STATEMENTS_H

#include <stdio.h>
#include <stdlib.h>
#include "commonFunc.h"
#include "heroStats.h"
#include "enemyStats.h"

const int MAX_ROWS = 100, MAX_COLUMNS = 100;
const int MIN_ROWS = 10, MIN_COLUMNS = 10;

// Utility
void clearHero(HeroData *heroes);

// Menu & UI Printouts
void welcome();
void gameInstructions();
void printNOH();
void printInvalidNOH();
void printChooseHeroes(int remainingHeroes);
void printDifficulty();
void printChoices(HeroData *heroes, char str[], char *first, int noh);
void gameSettings(HeroData heroes, char str[], int noh);
void asking(HeroData heroes, char str[], int pSize);
void allHeroesDead(int score);
void playerQuit(int score);
void mapRestrictions();

// Input Handlers
void readMapRestrictions(int *rows, int *col);

#endif
