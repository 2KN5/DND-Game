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
    
    // Main Menu
    menu(&heroes, dif, &exitGame);
    if(exitGame) return 0;
    
    // Set map restrictions.
    readMapRestrictions(&rows, &col);

    /* The map grows between levels, so size this for the largest map the game
    can ever reach rather than the starting dimensions. */
    enemies.capacity = MAX_GRID_SIZE * MAX_GRID_SIZE;
    enemies.data = malloc(sizeof(Enemy) * enemies.capacity);
    if(enemies.data == NULL){
        printf("Out of memory.\n");
        return 1;
    }
    
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

    // Free the grid (StartGame owns the grid once it starts resizing it.)
    free(enemies.data);
    return 0;
}
