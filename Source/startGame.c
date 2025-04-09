#include <stdio.h>
#include <stdlib.h>
#include "startGame.h"

void startGame(char ***grid, Hero hero[], Enemy enemy[], char dif[], int rows, int col){
    printGrid(grid, hero, enemy, dif, rows, col);
    printf("\n\nWelcome to the dungeon Player!\nAre you ready for the adventure?\n");
    while(enemy->numberOfEnemies > 0){
        while(!makeMove(grid, rows, col, hero, enemy)){
            clearScreen();
            printGrid(grid, hero, enemy, dif, rows, col);
            printf("\n\nInvalid Move!\n\n");
        }
    }
}
