#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "clearScreen.h"
#include "enemyDamage.h"
#include "enemyStats.h"
#include "heroDamage.h"
#include "heroStats.h"
#include "mainMenu.h"
#include "grid.h"
#include "roll.h"

void readMS(int *rows, int *col){
    char buffer[100] = {' '};
    while(buffer[0] != '\n'){
        clearScreen();
        printf("MAP RESTRICTIONS -> Has to be at least 5x5, and the Column Size(M), can be MAX = 92 (Fullscreen can't fit more squares.)\n\n");
        printf("Enter map size(N x M): ");
        while(scanf("%d%d", rows, col) != 2 || *rows < 5 || *col < 5 || *col > 92){
            clearScreen();
            printf("MAP RESTRICTIONS -> Has to be at least 5x5, and the Column Size(M), can be MAX = 92 (Fullscreen can't fit more squares.)\n\n");
            printf("Enter map size(N x M): ");
            clearBuffer();
        }
        fgets(buffer, sizeof(buffer), stdin);
    } 
}

int main(void){

    srand(time(NULL));

    int pSize, rows, col, mCount;
    char **grid, dif[10];
    struct Hero hero[MAX_PARTY_SIZE];
    struct Enemy enemy[MAX_MONSTER_COUNT];
    menu(hero, &pSize, dif);
    
    //Initialize hero stats.
    stats(hero, pSize);
    enemyStats(enemy, dif, &mCount);
    //Generate the map
    readMS(&rows, &col);
    createGrid(&grid, rows, col);
    printGrid(&grid, rows, col, hero, enemy, pSize, mCount, dif);
    freeGrid(&grid, rows);
    return 0;
}