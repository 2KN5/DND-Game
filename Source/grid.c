#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

void genFurniture(char ***grid, int rows, int col){
    int lowerBound = 1, upperBound = (rows * col) * 0.05f;
    int numberOfFurniture = rand() % (int)((upperBound + lowerBound - 1) + lowerBound), attempts = 0;
    while(numberOfFurniture && attempts < 1000){
        int x = rand() % (rows - 2) + 1;
        int y = rand() % (col - 2) + 1;
        if((*grid)[x][y] == '.'){
            //(*grid)[x][y] = '@';
            --numberOfFurniture;
        }
        ++attempts;
    }
}

void spawnHeroes(){

}

void spawnEnemies(){

}

void drawVertical_TOP(char ***grid, Walls wall[], int rows, int col, int *count){
    *count = 0;
    int MIN_WALL_SPACE = (int)fmax(2.0, col * 0.06f); // fmax(double, double)
    int upperBound = rows / 2, lowerBound = 1;
    //int upperBound = rows - 2, lowerBound = 1;

    //Create Walls
    for(int j = 2; j < col - 2; j += MIN_WALL_SPACE){
        if(*count == 0 || rand() % 3){
            int wallHeight = rand() % (int)(upperBound - lowerBound + 1) + lowerBound;
            for(int i = 1; i <= wallHeight; ++i){
                //(*grid)[i][j] = (rand() % WALL_CHANCE == 0 ? '.' : '#');
                (*grid)[i][j] = '#';
            }
            wall[*count].row = wallHeight;
            wall[*count].column = j;
            ++(*count);
        }
    }
}

void drawVertical_BOTTOM(char ***grid, Walls wall[], int rows, int col, int *count){
    *count = 0;
    int MIN_WALL_SPACE = (int)fmax(2.0, col * 0.06f); // fmax(double, double)
    int upperBound = rows - 2, lowerBound = (int)(rows / 2) + 1;
    //int upperBound = rows - 2, lowerBound = 1;

    //Create Walls
    for(int j = 2; j < col - 2; j += MIN_WALL_SPACE){
        if(*count == 0 || rand() % 3){
            int wallHeight = rand() % (int)(upperBound - lowerBound + 1) + lowerBound;
            for(int i = wallHeight; i <= rows - 1; ++i){
                //(*grid)[i][j] = (rand() % WALL_CHANCE == 0 ? '.' : '#');
                (*grid)[i][j] = '#';
            }
            wall[*count].row = wallHeight;
            wall[*count].column = j;
            ++(*count);
        }
    }
}

void drawHorizontal(char ***grid, Walls wall[], int rows, int col, int count){
    int prev = wall[0].column, currCol = 1;
    for(int j = 2; j < col - 2 && (currCol < count); ++j){
        if(j == wall[currCol].column){
            for(int k = prev; k < wall[currCol].column; ++k){
                //(*grid)[wall[currCol].row][k] = (rand() % WALL_CHANCE == 0 ? '.' : '#');
                (*grid)[wall[currCol].row][k] = '#';
            }
            prev = wall[currCol].column;
            ++currCol;
        }    
    }
}

void freeGrid(char ***grid, int rows){
    for(int i = 0; i < rows; ++i){
        free((*grid)[i]);
    }
    free(*grid);
}

void createGrid(char ***grid, int rows, int col){
    printf("Generating map...\n");
    *grid = (char**)malloc(sizeof(char*) * rows);
    for(int i = 0; i < rows; ++i){
        (*grid)[i] = (char*)malloc(sizeof(char) * col);
        for(int j = 0; j < col; ++j){
            (*grid)[i][j] = (i == 0 || i == rows - 1 || j == 0 || j == col - 1 ? '#' : '.');
        }
    }

    //Generate the walls    
    
    //Generating the upper walls.
    int countU = 0;
    Walls *upperWalls = malloc(sizeof(Walls) * col);
    drawVertical_TOP(grid, upperWalls, rows, col, &countU);
    drawHorizontal(grid, upperWalls, rows, col, countU);

    //Generating the lower walls.
    int countL = 0;
    Walls *lowerWalls = malloc(sizeof(Walls) * col);
    drawVertical_BOTTOM(grid, lowerWalls, rows, col, &countL);
    drawHorizontal(grid, lowerWalls, rows, col, countL);

    free(upperWalls);
    free(lowerWalls);
    genFurniture(grid, rows, col); //Generate furniture (>= 1 per room).
    //spawnHeroes();//Place heroes
    //spawnEnemies();//Place enemies
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

void returnColChar(int x, int width){
    if(x < 26){
        printf("%*c ", width, 'A' + x);
    } else if(x <= 100){
        printf("%*c%c", width, 'A' + x / 26 - 1, 'A' + x % 26);
    } 
}

void printGrid(char ***grid, int rows, int col, Hero hero[], Enemy enemy[], int partySize, int enemyCount, char *dif){

    printf("Creating map...\n");
    //Using the largest number as the width specifier.
    int width = numberOfDig(rows);

    //Printing the grid.
    clearScreen();
    printf("-DIFFICULTY: %s\n\n", dif);
    printf("%*c", width + 1, ' ');
    for(int i = 0; i < col; ++i){
        returnColChar(i, 2);
    }
    printf("\n");
    for(int i = 0; i < rows; ++i){
        printf("%*d ", width, i + 1);
        for(int j = 0; j < col; ++j){
            printf("%2c ", (*grid)[i][j]);
        }
        printf("\n");
    }
    /*
    printf("\n");
    for(int i = 0; i < partySize; ++i){
        printf("%c: %d ", hero[i].class, hero[i].health);
    }
    printf("\n");
    for(int i = 0; i < enemyCount; ++i){
        printf("%d ", enemy[i].health);
    }
    */
}
