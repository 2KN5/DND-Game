#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "enemyMove.h"

void enemyDamage(Hero hero, Enemy enemy){
    int side, dmg = 0;
    for(int i = 0; i < 2; ++i){
        side = roll();
        if(side % 2 == 0) ++dmg;
    }
    int heroDef = heroDefence(hero);
    printf("(%c) - Was attacked with %d Skull(s)!\nHe defended with %d White Shield(s)!\n\n", hero.class, dmg, heroDef);
    system("PAUSE");
}

int enemyDefence(Enemy enemy){
    int side, def = 0;
    for(int i = 0; i < 2; ++i){
        side = roll();
        if(side == 3) ++def;
    }
    return def;
}