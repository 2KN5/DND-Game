#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <stdio.h>
#include <stdlib.h>
#include "heroStats.h"

#define MAX_PARTY_SIZE 4

void clearBuffer();
void upperString(char *str);
int check(char *choice);
void clearHero(struct Hero h[MAX_PARTY_SIZE]);
void printChoices(char *str, struct Hero h[], int noh, char *first);
void menu(struct Hero hero[MAX_PARTY_SIZE], int *partySize, char dif[]);

#endif