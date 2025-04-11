#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <stdio.h>
#include <stdlib.h>
#include "heroStats.h"
#include "enemyStats.h"
#include "commonFunc.h"

int validString(char c[]);
void clearHero(HeroData *heroes);
void printChoices(HeroData *hero, char str[], char *first, int noh);
void menu(HeroData *hero, char dif[]);

#endif