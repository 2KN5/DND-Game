#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "heroMove.h"
#include "commonFunc.h"

void heroDamage(char ***grid, int x, int y, HeroData *heroes, EnemyData *enemies, int heroIndex, int enemyIndex, char pos[]){
    if(heroes->data[heroIndex].actions[0]){
        int side, dmg = 0;
        for(int i = 0; i < 3; ++i){
            side = roll();
            if(side % 2 == 0) ++dmg;
        }
        int enemyDef = enemyDefence(), totalDMG = (dmg - enemyDef <= 0 ? 0 : dmg - enemyDef);
        printf("(%c) - Attacked with %d Skull(s)!\nMonster defended with %d Black Shield(s) and lost %d Body Point(s)!\n\n", heroes->data[heroIndex].class, dmg, enemyDef, totalDMG);
        heroes->score += (int)(totalDMG * 30);
        if(enemies->data[enemyIndex].health - totalDMG <= 0){
            enemies->data[enemyIndex].health = 0;
            (*grid)[x][y] = '.';
            shiftEnemies(enemies, enemyIndex);
            printf("Killed enemy at %s!\n\n", pos);
            heroes->score += (int)(totalDMG * 50);
        } else {
            enemies->data[enemyIndex].health -= totalDMG;
            (*grid)[x][y] = '0' + enemies->data[enemyIndex].health;
        }
        heroes->data[heroIndex].actions[0] = 0;
    } else {
        printf("You have already attacked with this hero!\n\n");
    }
    pause();
}

int heroDefence(void){
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
        case 'H': return 12;  // Must match heroStats(). Omitting it zeroed the healer.
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

int checkHealerMove(char move[]){
    int curr = 2, count = 0, length = strlen(move) - 1;
    char str[6] = {0};
    while(curr <= length){
        if(!isalpha(move[curr])) return 0;
        if(count >= 4) return 0; // The only command here is "HEAL".
        str[count] = move[curr];
        ++count; ++curr;

    }
    str[count] = '\0';
    if(strcmp(str, "HEAL") != 0) return 0;
    return 1;
}