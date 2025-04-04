#include <stdio.h>
#include <stdlib.h>
#include "grid.h"
#include "mainMenu.h"

void createGrid(char ***grid, int rows, int col){
    printf("Generating map...\n");
    *grid = (char**)malloc(sizeof(char*) * rows);
    for(int i = 0; i < rows; ++i){
        (*grid)[i] = (char*)malloc(sizeof(char) * col);
        for(int j = 0; j < col; ++j){
            (*grid)[i][j] = (i == 0 || i == rows - 1 || j == 0 || j == col - 1 ? '#' : '.');
        }
    }
    system("PAUSE");
}

int numberOfDig(int x){
    int c = 0;
    while(x > 0){
        x /= 10;
        ++c;
    }
    return c;
}

void printGrid(char ***grid, int rows, int col, struct Hero hero[], int partySize, char *dif){

    printf("Creating map...\n");
    //Using the largest number as the width specifier.
    int width = numberOfDig(rows);

    //Printing the grid.
    system("cls");

    printf(" %*c", width, ' ');
    for(int i = 0; i < col; ++i){
        printf("%c ", 'A' + i);
    }
    printf("\n");
    for(int i = 0; i < rows; ++i){
        printf("%*d ", width, i + 1);
        for(int j = 0; j < col; ++j){
            printf("%c ", (*grid)[i][j]);
        }
        printf("\n");
    }
    for(int i = 0; i < partySize; ++i){
        printf("%c: %d ", hero[i].class, hero[i].health);
    }
}

void freeGrid(char ***grid, int rows){
    for(int i = 0; i < rows; ++i){
        free((*grid)[i]);
    }
    free(*grid);
}
