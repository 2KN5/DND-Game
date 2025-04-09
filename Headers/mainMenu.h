#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <stdio.h>
#include <stdlib.h>
#include "heroStats.h"
#include "enemyStats.h"
#include "commonFunc.h"

int validString(char c[]);
void upperString(char *str);
int check(char *choice);
void clearHero(Hero h[]);
void printChoices(char *str, Hero h[], int noh, char *first);
void menu(Hero hero[MAX_PARTY_SIZE], char dif[]);

#endif