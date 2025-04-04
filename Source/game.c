#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grid.h"
#include "mainMenu.h"
#include "heroStats.h"
#include "mainMenu.h"

int main(void){

    srand(time(NULL));

    int pSize, n, m;
    char **grid, dif[8];
    struct Hero hero[MAX_PARTY_SIZE];
    menu(hero, &pSize, dif);
    
    //Initialize hero stats.
    stats(hero, pSize);

    //Initialize map size
    printf("Enter map size(N x M): ");
    scanf("%d%d", &n, &m);
    clearBuffer();

    //Generate the map
    createGrid(&grid, n, m);
    printGrid(&grid, n, m, hero, pSize, dif);
    freeGrid(&grid, n);
    return 0;
}