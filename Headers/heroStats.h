#ifndef HERO_STATS_H
#define HERO_STATS_H

#include <stdio.h>
#include <stdlib.h>

struct Hero {
    char class;
    int numberOfMoves;
    int health;
    int x, y;
};

void stats(struct Hero h[], int count);

#endif