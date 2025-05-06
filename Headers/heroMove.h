#ifndef HERO_MOVE_H
#define HERO_MOVE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "heroStats.h"
#include "enemyMove.h"
#include "commonFunc.h"

// Player actions
void heroDamage(char ***grid, int x, int y, Hero *hero, EnemyData *enemies, int index, char pos[]);
int heroDefence(Hero hero);

// Healer Check
int checkHealerMove(Hero hero, char move[]);
void healAbility(HeroData *heroes, int healerIndex);

#endif