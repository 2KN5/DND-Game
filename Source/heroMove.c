#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heroMove.h"
#include "commonFunc.h"

void heroDamage(char ***grid, int x, int y, Hero hero, Enemy *enemy, char pos[]){
    int side, dmg = 0;
    for(int i = 0; i < 3; ++i){
        side = roll();
        if(side % 2 == 0) ++dmg;
    }
    int enemyDef = enemyDefence(*enemy), totalDMG = (dmg - enemyDef <= 0 ? 0 : dmg - enemyDef);
    printf("(%c) - Attacked with %d Skull(s)!\n", hero.class, dmg, enemyDef, totalDMG);
    if(enemy->health - totalDMG <= 0){
        enemy->health = 0;
        enemy->isAlive = 0;
        (*grid)[x][y] = '.';
        printf("Killed enemy at %s!\n\n", pos);
    } else {
        printf("Monster defended with %d Black Shield(s) and lost %d Body Point(s)!\n\n", enemyDef, totalDMG);
        enemy->health -= abs(dmg - enemyDef);
        (*grid)[x][y] = '0' + enemy->health;
    }
    system("PAUSE");
}

int heroDefence(Hero hero){
    int side, def = 0;
    for(int i = 0; i < 2; ++i){
        side = roll();
        if(side == 1 || side == 5) ++def;
    }
    return def;
}

