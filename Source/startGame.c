#include <stdio.h>
#include <stdlib.h>
#include "startGame.h"

void startGame(char ***grid, int rows, int col, HeroData *heroes, EnemyData *enemies, char dif[], int level, int *quit){
    int nextCommand;
    char result, move[28];
    printGrid(grid, rows, col, *heroes, *enemies, dif, level);
    welcome();
    while(1){
        while(enemies->totalEnemies > 0 && heroes->numberOfHeroes > 0){
            do{
                result = checkMove(*heroes, move);
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
                *quit = 1;
                freeGrid(grid, rows);
                return;
            } else if(!applyCommand(grid, rows, col, heroes, enemies, dif, result, move)){
                printGrid(grid, rows, col, *heroes, *enemies, dif, level);
                printf("\nInvalid Move!\n");
                printf("\n > B>R3D2 (Move)\n > E>A*F5 (Attack)\n > M>I3 (Spawn/Remove Enemy)\n > X (End Turn)\n > Q (Quit)\n");
                continue;
            }
            if(playerActions(heroes)){
                printGrid(grid, rows, col, *heroes, *enemies, dif, level);
                printf("\nAll heroes have used their actions! Enemy turn begins...\n\n");
                pause();
                printGrid(grid, rows, col, *heroes, *enemies, dif, level);
                enemyTurn(grid, rows, col, heroes, *enemies);
            }
            printGrid(grid, rows, col, *heroes, *enemies, dif, level);
        }
        if(heroes->numberOfHeroes <= 0){
            *quit = 0;
            freeGrid(grid, rows);
            return;
        }
        // Update the level, free the grid, and create a new one.
        ++level;
        printf("\nLevel Cleared! Moving to the next one...\n\n");
        resetHeroes(heroes);
        freeGrid(grid, rows);

        /* Grow the map ~15% per level, capped. These must be assigned back to
           rows/col: the rest of the loop and the freeGrid above, use them. */
        rows = (rows * 115 + 50) / 100;
        col  = (col  * 115 + 50) / 100;
        if(rows > MAX_GRID_SIZE) rows = MAX_GRID_SIZE;
        if(col  > MAX_GRID_SIZE) col  = MAX_GRID_SIZE;
        createGrid(grid, rows, col, heroes, enemies, dif);
        printGrid(grid, rows, col, *heroes, *enemies, dif, level);
    }
}
