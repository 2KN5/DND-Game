#ifndef HERO_STATS_H
#define HERO_STATS_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_PARTY_SIZE 5

typedef struct {
    char class;
    char positionChar[7];
    int x, y;
    int health;
    int numberOfMoves;
    int actions[2];
} Hero;

typedef struct {
    Hero data[MAX_PARTY_SIZE];
    int numberOfHeroes;
} HeroData;

// Hero stats and reset after level clear
void heroStats(HeroData *hero);
void resetHeroes(HeroData *heroes);

#endif