#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grid.h"
#include "mainMenu.h"
#include "heroStats.h"
#include "mainMenu.h"
#include "enemyDamage.h"
#include "heroDamage.h"

void readMS(int *rows, int *col){
    char buffer[100] = {};
    while(buffer[0] != '\n'){
        system("cls");
        printf("MAP RESTRICTIONS -> Has to be at least 5x5, and the Column Size(M), can be MAX = 92 (Fullscreen can't fit more squares.)\n\n");
        printf("Enter map size(N x M): ");
        while(scanf("%d%d", rows, col) != 2 || *rows < 5 || *col < 5 || *col > 92){
            system("cls");
            printf("MAP RESTRICTIONS -> Has to be at least 5x5, and the Column Size(M), can be MAX = 92 (Fullscreen can't fit more squares.)\n\n");
            printf("Enter map size(N x M): ");
            clearBuffer();
        }
        fgets(buffer, sizeof(buffer), stdin);
    } 
}

int main(void){

    srand(time(NULL));

    int pSize, rows, col;
    char **grid, dif[10];
    struct Hero hero[MAX_PARTY_SIZE];
    menu(hero, &pSize, dif);
    
    //Initialize hero stats.
    stats(hero, pSize);
    
    //Generate the map
    readMS(&rows, &col);
    createGrid(&grid, rows, col);
    printGrid(&grid, rows, col, hero, pSize, dif);
    freeGrid(&grid, rows);
    return 0;
}