#ifndef HERO_STATS_H
#define HERO_STATS_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_PARTY_SIZE 5

#define MIN_GRID_SIZE 10
#define MAX_GRID_SIZE 99

#define MAX_POSITION_LEN 6

// Keeps the buffer size and the grid cap from drifting apart.
_Static_assert(MAX_GRID_SIZE <= 99, "Position buffers assume at most 2 digits and 2 letters");

typedef struct {
    char class;
    char positionChar[MAX_POSITION_LEN];
    int x, y;
    int health;
    int numberOfMoves;
    int actions[2];
} Hero;

typedef struct {
    Hero data[MAX_PARTY_SIZE];
    int numberOfHeroes;
    int score;
} HeroData;

// Hero stats and reset after level clear
void heroStats(HeroData *heroes);
void resetHeroes(HeroData *heroes);

#endif