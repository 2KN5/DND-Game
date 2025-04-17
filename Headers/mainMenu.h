#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <stdio.h>
#include <stdlib.h>
#include "heroStats.h"
#include "enemyStats.h"
#include "commonFunc.h"

// Input validation and cleanup
int validString(char c[]);
void clearHero(HeroData *heroes);

// Menu display and hero selection
void printChoices(HeroData *hero, char str[], char *first, int noh);
void menu(HeroData *hero, char dif[], int *exitGame);


#endif