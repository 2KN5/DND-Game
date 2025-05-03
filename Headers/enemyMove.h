#ifndef ENEMY_MOVE_H
#define ENEMY_MOVE_H

#include <stdio.h>
#include <stdlib.h>
#include "enemyStats.h"
#include "heroMove.h"
#include "commonFunc.h"

// Enemy actions
void enemyDamage(char ***grid, int x, int y, HeroData *heroes, int index);
int enemyDefence(Enemy enemy);

#endif