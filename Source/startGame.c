#include <stdio.h>
#include <stdlib.h>
#include "startGame.h"

void startGame(char ***grid, int rows, int col, HeroData *heroes, EnemyData *enemies, char dif[], int level){
    int nextCommand;
    char result, move[28];
    printGrid(grid, rows, col, *heroes, *enemies, dif, level);
    welcome();
    while(1){
        while(enemies->totalEnemies > 0 && heroes->numberOfHeroes > 0){
            do{
                result = checkMove(grid, rows, col, *heroes, *enemies, move);
                if(result == 'I'){
                    printGrid(grid, rows, col, *heroes, *enemies, dif, level);
                    printf("\nInvalid Move!\n");
                    printf("\n > B>R3D2 (Move)\n > E>A*F5 (Attack)\n > M>I3 (Spawn/Remove Enemy)\n > X (End Turn)\n > Q (Quit)\n");
                }
            } while(result == 'I');
            nextCommand = otherCommands(result, grid, rows, col, heroes, *enemies, dif, level);
            if(nextCommand == 0){
                // Let the enemy play
                enemyTurn(grid, rows, col, heroes, *enemies);
            } else if(nextCommand == 1){
                return;
            } else if(!applyCommand(grid, rows, col, heroes, enemies, dif, result, move)){
                printGrid(grid, rows, col, *heroes, *enemies, dif, level);
                printf("\nInvalid Move!\n");
                printf("\n > B>R3D2 (Move)\n > E>A*F5 (Attack)\n > M>I3 (Spawn/Remove Enemy)\n > X (End Turn)\n > Q (Quit)\n");
                continue;
            }
            if(playerActions(heroes)){
                printf("All heroes have used their actions! Enemy turn begins...\n\n");
                enemyTurn(grid, rows, col, heroes, *enemies);
            }
            printGrid(grid, rows, col, *heroes, *enemies, dif, level);
        }
        if(heroes->numberOfHeroes <= 0){
            printf("\nAll heroes have perished. Good luck next time.\n");
            return;
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
