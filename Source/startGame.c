#include <stdio.h>
#include <stdlib.h>
#include "startGame.h"

int otherCommands(char c, char ***grid, int rows, int col, HeroData *heroes, EnemyData enemies, char dif[]){
    if(c == 'X'){
        for(int i = 0; i < heroes->numberOfHeroes; ++i){
            heroes->data[i].actions[0] = 1;
            heroes->data[i].actions[1] = 1;
        }
        printf("\nPlayer turn over. Enemies are making their move...\n\n");
        system("PAUSE");
        return 0;
    }
    if(c == 'Q'){
        char choice = 'N';
        while(1){
            printf("\nAre you sure you want to quit the game?\n(Y/N): ");
            if(!check(&choice)){
                printGrid(grid, rows, col, *heroes, enemies, dif);
                printf("\nInvalid Choice!\n");
                continue;
            }
            break;
        } 
        return (choice == 'N' ? 0 : 1);
    }
    return 2;
}

void startGame(char ***grid, int rows, int col, HeroData *heroes, EnemyData *enemies, char dif[]){
    int nextCommand;
    char result, move[28];
    printGrid(grid, rows, col, *heroes, *enemies, dif);
    printf("\nWelcome to the dungeon Player!\nAre you ready for the adventure?\n");
    while(enemies->totalEnemies > 0){
        do{
            result = checkMove(grid, rows, col, *heroes, *enemies, move);
            if(result == 'I'){
                printGrid(grid, rows, col, *heroes, *enemies, dif);
                printf("\nInvalid Move!\n");
            }
        } while(result == 'I');
        nextCommand = otherCommands(result, grid, rows, col, heroes, *enemies, dif);
        if(nextCommand == 0){
            //Let the enemy play
            printGrid(grid, rows, col, *heroes, *enemies, dif);
            continue;
        } else if(nextCommand == 1){
            return;
        } else if(!applyCommand(grid, rows, col, heroes, enemies, dif, result, move)){
            printGrid(grid, rows, col, *heroes, *enemies, dif);
            printf("\nInvalid Move!\n");
            continue;
        }
        printGrid(grid, rows, col, *heroes, *enemies, dif);
    }
}
