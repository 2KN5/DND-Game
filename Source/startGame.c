#include <stdio.h>
#include <stdlib.h>
#include "startGame.h"

int otherCommands(char c){
    if(c == 'X') return 0; // Continue loop, let the enemy play
    if(c == 'Q'){
        char choice = 'N';
        printf("\nAre you sure you want to quit the game?\n(Y/N): ");
        if(!check(&choice)) return 0;
        return (choice == 'N' ? 0 : 1);
    }
    return 2;
}

void startGame(char ***grid, int rows, int col, HeroData *heroes, EnemyData *enemies, char dif[]){
    int nextCommand;
    char result;
    printGrid(grid, rows, col, *heroes, *enemies, dif);
    printf("\n\nWelcome to the dungeon Player!\nAre you ready for the adventure?\n");
    while(enemies->totalEnemies > 0){
        do{
            result = checkMove(grid, rows, col, *heroes, *enemies);
            if(result == 'I'){
                //clearScreen();
                printGrid(grid, rows, col, *heroes, *enemies, dif);
                printf("\nInvalid Move!\n");
            }
        } while(result == 'I');
        printf("\nValid Move! %c\n", result);
        system("PAUSE");
        nextCommand = otherCommands(result);
        if(nextCommand == 0){
            //Let the enemy play
            //clearScreen();
            printGrid(grid, rows, col, *heroes, *enemies, dif);
            continue;
        } else if(nextCommand == 1){
            return;
        } 
        applyMove(grid, rows, col, heroes, enemies, result);
        //clearScreen();
        printGrid(grid, rows, col, *heroes, *enemies, dif);
    }
}
