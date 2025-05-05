#ifndef PRINT_STATEMENTS_H
#define PRINT_STATEMENTS_H

#include <stdio.h>
#include <stdlib.h>
#include "commonFunc.h"
#include "heroStats.h"
#include "enemyStats.h"

// Printing the messages.
void gameInstructions();
void printNOH();
void printInvalidNOH();
void printChooseHeroes(int remainingHeroes);
void printDifficulty();
void welcome();

// Reading map restrictions
void readMapRestrictions(int *rows, int *col);

#endif