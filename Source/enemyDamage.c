#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "enemyDamage.h"

void enemyDamage(Enemy *enemy){
    int side, dmg = 0;
    for(int i = 0; i < 2; ++i){
        side = roll();
        if(side % 2 == 0) ++dmg;
    }
    enemy->damage = dmg;
}

void enemyDefence(Enemy *enemy){
    int side, def = 0;
    for(int i = 0; i < 2; ++i){
        side = roll();
        if(side == 3) ++def;
    }
    enemy->shields = def;
}