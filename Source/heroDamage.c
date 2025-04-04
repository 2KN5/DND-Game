#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heroStats.h"
#include "roll.h"

void heroDamage(struct Hero hero){
    int side, dmg = 0;
    for(int i = 0; i < 3; ++i){
        side = roll();
        if(side % 2 == 0) ++dmg;
    }
    hero.damage = dmg;
}

void heroDefence(struct Hero hero){
    int side, def = 0;
    for(int i = 0; i < 2; ++i){
        side = roll();
        if(side == 1 || side == 5) ++def;
    }
    hero.shields = def;
}

