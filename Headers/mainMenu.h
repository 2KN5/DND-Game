#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <stdio.h>
#include <stdlib.h>
#include "heroStats.h"
#include "enemyStats.h"
#include "commonFunc.h"
#include "printStatements.h"

// Input validation
int validString(char c[]);

// Menu display and hero selection
void printChoices(HeroData *hero, char str[], char *first, int noh);
void menu(HeroData *hero, char dif[], int *exitGame);


#endif