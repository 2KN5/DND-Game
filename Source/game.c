#include <stdio.h>
#include <stdlib.h>
#include "startGame.h"

int main(void){

    srand(time(NULL));

    // Game Instructions.
    gameInstructions();
    
    int rows, col, exitGame = 0, level = 1;
    char **grid, dif[10], pos[6];
    
    HeroData heroes;
    EnemyData enemies;
    enemies.data = malloc(sizeof(Enemy) * (rows * col));
    
    menu(&heroes, dif, &exitGame);
    if(exitGame) return 0;
    heroStats(&heroes);
    
    // Set map restrictions.
    readMapRestrictions(&rows, &col);
    enemies.data = malloc(sizeof(Enemy) * (rows * col));
    
    // Generate the map.
    printf("\nCreating map...\n\n"); pause();
    createSG(&grid, rows, col, &heroes, &enemies, dif);
    
    // Welcome to the dungeon!
    startGame(&grid, rows, col, &heroes, &enemies, dif, level);
    
    // Free the grid.
    free(enemies.data);
    freeGrid(&grid, rows);
    return 0;
}
