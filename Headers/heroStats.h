#ifndef HERO_STATS_H
#define HERO_STATS_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_PARTY_SIZE 4

typedef struct {
    char class;
    int x, y;
    int damage;
    int shields;
    int health;
    int numberOfMoves;
} Hero;

typedef struct {
    Hero data[MAX_PARTY_SIZE];
    int numberOfHeroes;
} HeroData;

void heroStats(HeroData *hero);

#endif