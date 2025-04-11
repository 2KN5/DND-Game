#include <stdio.h>
#include <stdlib.h>
#include "startGame.h"

void startGame(char ***grid, int rows, int col, HeroData *heroes, EnemyData *enemies, char dif[]){
    printGrid(grid, rows, col, *heroes, *enemies, dif);
    printf("\n\nWelcome to the dungeon Player!\n\nAre you ready for the adventure?\n");
    while(enemies->totalEnemies > 0){
        while(!makeMove(grid, rows, col, *heroes, *enemies)){
            clearScreen();
            printGrid(grid, rows, col, *heroes, *enemies, dif);
            printf("\n\nInvalid Move!\n\n");
        }
        clearScreen();
        printGrid(grid, rows, col, *heroes, *enemies, dif);
        printf("\n\nValid Move!\n\n");
    }
}
