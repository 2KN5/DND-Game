#include <stdio.h>
#include <stdlib.h>
#include "startGame.h"

int main(void){

    srand(time(NULL));

    int rows, col;
    char **grid, dif[10];

    HeroData heroes;
    EnemyData enemies;

    menu(&heroes, dif);
    heroStats(&heroes);
    
    //Set map restrictions.
    readMS(&rows, &col);
    enemies.data = malloc(sizeof(Enemy) * (rows * col));
    
    //Generate the map.
    createGrid(&grid, rows, col, &heroes, &enemies, dif);
    printGrid(&grid, rows, col, heroes, enemies, dif);
    
    //Welcome to the dungeon!
    startGame(&grid, rows, col, &heroes, &enemies, dif);
    
    //Free the grid.
    freeGrid(&grid, rows);
    return 0;
}