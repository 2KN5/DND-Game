#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
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
    Hero hero[MAX_PARTY_SIZE];
    menu(hero, &pSize, dif);
    
    //Initialize hero stats.
    stats(hero, pSize);
    
    //Generate the map
    readMS(&rows, &col);
    Enemy *enemy = malloc(sizeof(Enemy) * (rows * col));
    createGrid(&grid, hero, pSize, enemy, dif, rows, col);
    printGrid(&grid, rows, col, hero, enemy, pSize, mCount, dif);
    /*
    printf("\n\nWelcome to the dungeon Player!\nTime to begin.\nMake your move: ");
    char move[28];
    while(1){
        fgets(move, sizeof(move), stdin);
        if(validString(move)){
            printGrid(&grid, rows, col, hero, enemy, pSize, mCount, dif);
            printf("\n\nInvalid Move!\nMake your move: ");
            continue;
        }
        break;
    }
    printf("%s\n", move);
    */
    freeGrid(&grid, rows);
    return 0;
}