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
    pause();
}

int heroDefence(Hero hero){
    int side, def = 0;
    for(int i = 0; i < 2; ++i){
        side = roll();
        if(side == 1 || side == 5) ++def;
    }
    return def;
}

int maxHeroHealth(char class){
    switch(class){
        case 'B': return 8;
        case 'W': return 4;
        case 'D': return 7;
        case 'E': return 6;
        default: return 0;
    }
}

void healAbility(HeroData *heroes, int healerIndex){
    int count = 0;
    if(heroes->data[healerIndex].actions[0]){
        for(int i = 0; i < heroes->numberOfHeroes; i++){
            if(healerIndex == i) continue;
            int dx = abs(heroes->data[healerIndex].x - heroes->data[i].x);
            int dy = abs(heroes->data[healerIndex].y - heroes->data[i].y);
            if(dx + dy <= 5){
                heroes->data[i].health += 2;
                int maxhealth = maxHeroHealth(heroes->data[i].class);
                if(maxhealth < heroes->data[i].health){
                    heroes->data[i].health = maxhealth;
                }
                ++count;
            }
        }
        if(!count){
            printf("\nNo allies nearby!\n\n");
        } else {
            printf("\nHealed %d %s!\n\n", count, (count == 1 ? "ally" : "allies")); 
            heroes->data[healerIndex].actions[0] = 0;
        }
    } else {
        printf("\nYou have already healed nearby allies once!\n\n");
    }
    pause();
}

int checkHealerMove(Hero hero, char move[]){
    int curr = 2, count = 0, length = strlen(move) - 1;
    char str[5];
    while(curr <= length){
        if(!isalpha(move[curr])) return 0;
        while(curr <= length){
            str[count] = move[curr];
            ++count; ++curr;
        }
    }
    if(strcmp(str, "HEAL") != 0) return 0;
    return 1;
}