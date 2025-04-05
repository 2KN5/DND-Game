#ifndef HERO_STATS_H
#define HERO_STATS_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_PARTY_SIZE 4

typedef struct Hero {
    char class;
    int numberOfMoves;
    int damage;
    int shields;
    int health;
    int x, y;
} Hero;

void stats(Hero h[], int count);

#endif