#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heroMove.h"
#include "commonFunc.h"

void heroDamage(char ***grid, int x, int y, Hero *hero, EnemyData *enemies, int index, char pos[]){
    if(hero->actions[0]){
        int side, dmg = 0;
        for(int i = 0; i < 3; ++i){
            side = roll();
            if(side % 2 == 0) ++dmg;
        }
        int enemyDef = enemyDefence(enemies->data[index]), totalDMG = (dmg - enemyDef <= 0 ? 0 : dmg - enemyDef);
        printf("(%c) - Attacked with %d Skull(s)!\nMonster defended with %d Black Shield(s) and lost %d Body Point(s)!\n\n", hero->class, dmg, enemyDef, totalDMG);
        if(enemies->data[index].health - totalDMG <= 0){
            enemies->data[index].health = 0;
            (*grid)[x][y] = '.';
            shiftEnemies(enemies, index);
            printf("Killed enemy at %s!\n\n", pos);
        } else {
            enemies->data[index].health -= totalDMG;
            (*grid)[x][y] = '0' + enemies->data[index].health;
        }
        hero->actions[0] = 0;
    } else {
        printf("You have already attacked with this hero!\n\n");
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

