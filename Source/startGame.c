#include <stdio.h>
#include <stdlib.h>
#include "startGame.h"

void playerActions(HeroData *heroes){
    int total = 0;
    for(int i = 0; i < heroes->numberOfHeroes; ++i){
        total += heroes->data[i].actions[0] + heroes->data[i].actions[1];
    }
    if(total == 0){
        for(int i = 0; i < heroes->numberOfHeroes; ++i){
            heroes->data[i].actions[0] = 1;
            heroes->data[i].actions[1] = 1;
        }
        printf("\nAll heroes have used their actions! Enemy turn begins...\n\n");
        system("PAUSE");
    }
}

int otherCommands(char c, char ***grid, int rows, int col, HeroData *heroes, EnemyData enemies, char dif[], int level){
    if(c == 'X'){
        for(int i = 0; i < heroes->numberOfHeroes; ++i){
            heroes->data[i].actions[0] = 1;
            heroes->data[i].actions[1] = 1;
        }
        printf("\nTurn ended! Let's see what the enemies are up to...\n\n");
        system("PAUSE");
        return 0;
    }
    if(c == 'Q'){
        char choice = 'N';
        while(1){
            printf("\nAre you sure you want to quit the game?\n(Y/N): ");
            if(!check(&choice)){
                printGrid(grid, rows, col, *heroes, enemies, dif, level);
                printf("\nInvalid Choice!\n");
                continue;
            }
            break;
        } 
        return (choice == 'N' ? 0 : 1);
    }
    return 2;
}

void startGame(char ***grid, int rows, int col, HeroData *heroes, EnemyData *enemies, char dif[], int level){
    int nextCommand;
    char result, move[28];
    printGrid(grid, rows, col, *heroes, *enemies, dif, level);
    printf("\nWelcome to the dungeon Player!\nAre you ready for the adventure?\n");
    while(1){
        while(enemies->totalEnemies > 0){
            do{
                result = checkMove(grid, rows, col, *heroes, *enemies, move);
                if(result == 'I'){
                    printGrid(grid, rows, col, *heroes, *enemies, dif, level);
                    printf("\nInvalid Move!\n");
                }
            } while(result == 'I');
            nextCommand = otherCommands(result, grid, rows, col, heroes, *enemies, dif, level);
            if(nextCommand == 0){
                // Let the enemy play
                printGrid(grid, rows, col, *heroes, *enemies, dif, level);
                continue;
            } else if(nextCommand == 1){
                return;
            } else if(!applyCommand(grid, rows, col, heroes, enemies, dif, result, move)){
                printGrid(grid, rows, col, *heroes, *enemies, dif, level);
                printf("\nInvalid Move!\n");
                continue;
            }
            playerActions(heroes);
            printGrid(grid, rows, col, *heroes, *enemies, dif, level);
        }

        // Update the level, free the grid, and create a new one.
        ++level;
        printf("\nLevel Cleared! Moving to the next one...\n\n");
        freeGrid(grid, rows);

        // Create the new grid.
        rows += 4; col += 4;
        createGrid(grid, rows, col, heroes, enemies, dif);
        printGrid(grid, rows, col, *heroes, *enemies, dif, level);
    }
}
