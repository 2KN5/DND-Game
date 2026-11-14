#include <stdio.h>
#include <stdlib.h>
#include "startGame.h"

int main(void){

    srand(time(NULL));

    // Game Instructions.
    gameInstructions();
    
    // Variables.
    int rows, col, exitGame = 0, level = 1, quit;
    char **grid, dif[10];
    
    HeroData heroes;
    EnemyData enemies;
    enemies.data = malloc(sizeof(Enemy) * (rows * col));
    
    // Main Menu
    menu(&heroes, dif, &exitGame);
    if(exitGame) return 0;
    
    // Set map restrictions.
    readMapRestrictions(&rows, &col);
    enemies.data = malloc(sizeof(Enemy) * (rows * col));
    
    // Generate the map.
    printf("\nCreating map...\n\n"); pause();
    createSG(&grid, rows, col, &heroes, &enemies, dif);
    
    // Welcome to the dungeon!
    startGame(&grid, rows, col, &heroes, &enemies, dif, level, &quit);

    // Did the player die or quit?
    clearScreen();
    if(quit){
        playerQuit(heroes.score);
    } else {
        allHeroesDead(heroes.score);
    }

    // Free the grid.
    free(enemies.data);
    freeGrid(&grid, rows);
    return 0;
}
