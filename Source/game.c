#include <stdio.h>
#include <stdlib.h>
#include "startGame.h"

int main(void){

    srand(time(NULL));

    int rows, col, exitGame = 0;
    char **grid, dif[10], pos[6];

    HeroData heroes;
    EnemyData enemies;
    enemies.data = malloc(sizeof(Enemy) * (rows * col));

    menu(&heroes, dif, &exitGame);
    if(exitGame) return 0;
    heroStats(&heroes);
    
    //Set map restrictions.
    readMS(&rows, &col);
    enemies.data = malloc(sizeof(Enemy) * (rows * col));
    
    //Generate the map.
    printf("Creating map...\n");
    createGrid(&grid, rows, col, &heroes, &enemies, dif);
    
    //Welcome to the dungeon!
    startGame(&grid, rows, col, &heroes, &enemies, dif);
    
    //Free the grid.
    free(enemies.data);
    freeGrid(&grid, rows);
    return 0;
}
