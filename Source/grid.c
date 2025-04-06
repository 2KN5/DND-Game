#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

void returnColChar(int x, int width){
    if(x < 26){
        printf("%*c ", width, 'A' + x);
    } else if(x <= 100){
        printf("%*c%c", width, 'A' + x / 26 - 1, 'A' + x % 26);
    } 
}

int numberOfDig(int x){
    int c = 0;
    while(x > 0){
        x /= 10;
        ++c;
    }
    return c;
}

void genFurniture(char ***grid, int rows, int col){
    int lowerBound = 1, upperBound = (int)fmax(1.0, (rows * col) * 0.04f);
    int numberOfFurniture = rand() % (upperBound + lowerBound - 1) + lowerBound, attempts = 0;
    while(numberOfFurniture && attempts <= 1000){
        int x = rand() % (rows - 2) + 1;
        int y = rand() % (col - 2) + 1;
        if((*grid)[x][y] == '.'){
            (*grid)[x][y] = '@';
            --numberOfFurniture;
        }
        ++attempts;
    }
}

void createHallway(char ***grid, int rows, int col){
    int hway = rows / 2;
    for(int j = 1; j < col - 1; ++j){
        (*grid)[hway][j] = '&';
    }
}

void createDoor(char ***grid, int currentRow, int upper, int lower){
    char c = '&';
    int door = rand() % (upper - lower + 1) + lower;
    (*grid)[currentRow][door] = c;
    (*grid)[currentRow + 1][door] = c;
    (*grid)[currentRow - 1][door] = c;
}

void clearEntr(char ***grid, int rows, int col){
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < col; ++j){
            if((*grid)[i][j] == '&') (*grid)[i][j] = '.';
        }
    }
}

void spawnHeroes(){

}

void spawnEnemies(){

}

void freeGrid(char ***grid, int rows){
    for(int i = 0; i < rows; ++i){
        free((*grid)[i]);
    }
    free(*grid);
}

void drawVertical_TOP(char ***grid, Walls wall[], int rows, int col, int *count){

    //Values.
    *count = 0;
    int MIN_WALL_SPACE = (int)fmax(3.0, col * 0.1f), start = rand() % ((col / 2) - 1) + 2;;
    int upperBound = (rows % 2 != 0 ? (int)(rows / 2) - 1 : (rows / 2) - 1);
    int lowerBound = (rows >= 8 ? 3 : 2);
    
    //Draw Walls.
    if(lowerBound > upperBound) return;
    for(int j = start; j < col - 2; j += MIN_WALL_SPACE){
        if(*count == 0 || rand() % 3 != 0){
            int wallHeight = rand() % (upperBound - lowerBound + 1) + lowerBound;
            for(int i = 1; i <= wallHeight; ++i){
                (*grid)[i][j] = (rand() % WALL_CHANCE == 0 ? '.' : '#');
                //(*grid)[i][j] = '#';
            }
            wall[*count].row = wallHeight;
            wall[*count].column = j;
            ++(*count);
        }
    }

    //Connect to the next wall.
    if(*count == 1) return;
    int prevCol = wall[0].column, prevRow = wall[0].row, curr = 1;
    for(int j = wall[curr].column; j <= wall[*count - 1].column; ++j){
        if(j == wall[curr].column){
            for(int k = wall[curr].row; k >= prevRow; --k){
                (*grid)[k][prevCol] = (rand() % WALL_CHANCE == 0 ? '.' : '#');
                //(*grid)[k][prevCol] = '#';
            }
            prevRow = wall[curr].row;
            prevCol = wall[curr].column;
            ++curr;
        }    
    }
}

void drawVertical_BOTTOM(char ***grid, Walls wall[], int rows, int col, int *count){

    //Values.
    *count = 0;
    int MIN_WALL_SPACE = (int)fmax(3.0, col * 0.1f), start = rand() % ((col / 2) - 1) + 2;
    int upperBound = (rows >= 9 ? rows - 4 : rows - 3);
    int lowerBound = (rows % 2 != 0 ? (rows + 1) / 2 : (rows / 2) + 1);
    
    //Draw Walls.
    if(lowerBound > upperBound) return;
    for(int j = start; j < col - 2; j += MIN_WALL_SPACE){
        if(*count == 0 || rand() % 3 != 0){
            int wallHeight = rand() % (upperBound - lowerBound + 1) + lowerBound;
            for(int i = wallHeight; i < rows - 1; ++i){
                (*grid)[i][j] = (rand() % WALL_CHANCE == 0 ? '.' : '#');
                //(*grid)[i][j] = '#';
            }
            wall[*count].row = wallHeight;
            wall[*count].column = j;
            ++(*count);
        }
    }
    
    //Connect to the next wall.
    if(*count == 1) return;
    int prevCol = wall[0].column, prevRow = wall[0].row, curr = 1;
    for(int j = wall[curr].column; j <= wall[*count - 1].column; ++j){
        if(j == wall[curr].column){
            for(int k = wall[curr].row; k < prevRow; ++k){
                (*grid)[k][prevCol] = (rand() % WALL_CHANCE == 0 ? '.' : '#');
                //(*grid)[k][prevCol] = '#';
            }
            prevRow = wall[curr].row;
            prevCol = wall[curr].column;
            ++curr;
        }    
    }
}

void drawHorizontal(char ***grid, Walls wall[], int rows, int col, int count){

    //Check if there are more than 2 walls, to avoid issues.
    if(count == 0){
        return;
    } else if(count == 1){
        for(int j = 0; j < wall[0].column; ++j){
            (*grid)[wall[0].row][j] = '#';
        }
        for(int j = wall[0].column; j < col; ++j){
            (*grid)[wall[0].row][j] = '#';
        }
        createDoor(grid, wall[0].row, wall[0].column - 1, 1);
        createDoor(grid, wall[0].row, col - 2, wall[0].column);
        return;
    }

    //Connect the first column to the wall.
    for(int j = 0; j < wall[0].column; ++j){
        //(*grid)[wall[0].row][j] = (rand() % WALL_CHANCE == 0 ? '.' : '#');
        (*grid)[wall[0].row][j] = '#';
    }
    createDoor(grid, wall[0].row, wall[0].column - 1, 1);

    //Connect all the other columns.
    int prevCol = wall[0].column, prevRow = wall[0].row, curr = 1;
    for(int j = wall[curr].column; j <= wall[count - 1].column; ++j){
        if(j == wall[curr].column){
            for(int k = prevCol; k < wall[curr].column; ++k){
                //(*grid)[wall[curr].row][k] = (rand() % WALL_CHANCE == 0 ? '.' : '#');
                (*grid)[wall[curr].row][k] = '#';
            }
            createDoor(grid, wall[curr].row, wall[curr].column - 1, prevCol + 1);
            prevRow = wall[curr].row;
            prevCol = wall[curr].column;
            ++curr;
        }    
    }

    //Connect the last column to the wall.
    for(int j = wall[count - 1].column; j < col; ++j){
        //(*grid)[wall[count - 1].row][j] = (rand() % WALL_CHANCE == 0 ? '.' : '#');
        (*grid)[wall[count - 1].row][j] = '#';
    }
    createDoor(grid, wall[count - 1].row, col - 2, wall[count - 1].column + 1);
}

void createGrid(char ***grid, int rows, int col){

    //Create the starting grid.
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
    createHallway(grid, rows, col);
    genFurniture(grid, rows, col); //Generate furniture (>= 1 per room).
    clearEntr(grid, rows, col);
    //spawnHeroes();//Place heroes
    //spawnEnemies();//Place enemies
    system("PAUSE");
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
