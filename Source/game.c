#include <stdio.h>
#include <stdlib.h>
#include "startGame.h"

int main(void){

    srand(time(NULL));

    int rows, col;
    char **grid, dif[10];
    Hero hero[MAX_PARTY_SIZE];
    menu(hero, dif);
    
    //Initialize hero stats.
    stats(hero);
    
    //Generate the map
    readMS(&rows, &col);
    Enemy *enemy = malloc(sizeof(Enemy) * (rows * col));
    createGrid(&grid, hero, enemy, dif, rows, col);

    //Welcome to the dungeon!
    startGame(&grid, hero, enemy, dif, rows, col);
    
    //Free the grid.
    freeGrid(&grid, rows);
    return 0;
}