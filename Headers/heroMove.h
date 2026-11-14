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
void heroDamage(char ***grid, int x, int y, HeroData *heroes, EnemyData *enemies, int heroIndex, int enemyIndex, char pos[]);
int heroDefence(void);

// Healer Check
int maxHeroHealth(char class);
int checkHealerMove(char move[]);
void healAbility(HeroData *heroes, int healerIndex);

#endif