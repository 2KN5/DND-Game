#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "enemyMove.h"

void enemyDamage(char ***grid, int x, int y, HeroData *heroes, int index){
    int side, dmg = 0;
    for(int i = 0; i < 2; ++i){
        side = roll();
        if(side % 2 == 0) ++dmg;
    }
    int heroDef = heroDefence(heroes->data[index]), totalDMG = (dmg - heroDef <= 0 ? 0 : dmg - heroDef);;
    printf("(%c) - Was attacked with %d Skull(s)!\nHe defended with %d White Shield(s)!\n\n", heroes->data[index].class, dmg, heroDef);
    if(heroes->data[index].health - totalDMG <= 0){
        heroes->data[index].health = 0;
        (*grid)[x][y] = '.';
        printf("(%c) was killed at %s!\n\n", heroes->data[index].class, heroes->data[index].positionChar);
        shiftHeroes(heroes, index);
    } else {
        heroes->data[index].health -= totalDMG;
    }
}

int enemyDefence(Enemy enemy){
    int side, def = 0;
    for(int i = 0; i < 2; ++i){
        side = roll();
        if(side == 3) ++def;
    }
    return def;
}