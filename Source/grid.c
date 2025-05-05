#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

int numberOfDig(int x){
    int c = 0;
    while(x > 0){
        x /= 10;
        ++c;
    }
    return c;
}

void printColChar(int x, int width){
    if(x < 26){
        printf("%*c ", width, 'A' + x);
    } else if(x <= 100){
        printf("%*c%c", width, 'A' + x / 26 - 1, 'A' + x % 26);
    } 
}

void getPositionChar(int x, int y, char pos[]){
    char numbers[3];
    returnColChar(y, pos);
    sprintf(numbers, "%d", x);
    strcat(pos, "-");
    strcat(pos, numbers);
}

void genFurniture(char ***grid, int rows, int col){
    int area = rows * col;
    int lowerBound = (col >= 50 || rows >= 50 ? area * 0.01 : 1), upperBound = (col >= 50 || rows >= 50 ? area * 0.03 : (int)fmax(1.0, area * 0.02));
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

void floodFillRoom(char **grid, int rows, int col, int ***roomMap, int x, int y, int roomID){
    if(x < 0 || x >= rows || y < 0 || y >= col) return;
    if(grid[x][y] != '.' || (*roomMap)[x][y] != -1) return;

    (*roomMap)[x][y] = roomID;
    floodFillRoom(grid, rows, col, roomMap, x + 1, y, roomID);
    floodFillRoom(grid, rows, col, roomMap, x - 1, y, roomID);
    floodFillRoom(grid, rows, col, roomMap, x, y + 1, roomID);
    floodFillRoom(grid, rows, col, roomMap, x, y - 1, roomID);
}

void countRooms(char **grid, int rows, int col, int ***roomMap, int *count){
    *count = 0;
    for(int i = 1; i < rows; ++i){
        for(int j = 1; j < col; ++j){
            if(grid[i][j] == '.' && (*roomMap)[i][j] == -1){
                ++(*count);
                floodFillRoom(grid, rows, col, roomMap, i, j, *count);
            }
        }
    }
}   

void clear_Rooms_Hallway(char ***grid, int rows, int col){
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < col; ++j){
            if((*grid)[i][j] == '&') (*grid)[i][j] = '.';
        }
    }
}

void spawnHeroes(char ***grid, int rows, int col, HeroData *hero){
    int i = 0;
    char str[6];
    while(i < hero->numberOfHeroes){
        int x = rand() % (rows - 2) + 1;
        int y = rand() % (col - 2) + 1;
        if((*grid)[x][y] == '.'){
            (*grid)[x][y] = hero->data[i].class;
            hero->data[i].x = x; 
            hero->data[i].y = y;
            getPositionChar(x + 1, y, hero->data[i].positionChar);
            ++i;
        }
    }
}

void spawnEnemies(char ***grid, int rows, int col, HeroData *hero, EnemyData *enemy, int roomArea[rows * col][2], int count){
    int noe = 0, attempts = 0;
    while(noe < enemy->enemiesPerRoom && attempts < 1000){
        int x = roomArea[rand() % count][0];
        int y = roomArea[rand() % count][1];
        if((*grid)[x][y] == '.'){
            int index = enemy->totalEnemies + noe;
            (*grid)[x][y] = '0' + enemy->data[index].health;
            enemy->data[index].x = x; 
            enemy->data[index].y = y;
            ++noe; 
        }
        ++attempts;
    }
    enemy->totalEnemies += noe;
}

void populateRooms(char ***grid, int rows, int col, HeroData *hero, EnemyData *enemy, int **roomMap, int numberOfRooms, char dif[]){
    enemy->totalEnemies = 0;
    int area = rows * col;
    for(int room = 1; room <= numberOfRooms; ++room){
        int count = 0, roomArea[area][2];

        // Get area for each room.
        for(int i = 1; i < rows - 1; ++i){
            for(int j = 1; j < col - 1; ++j){
                if((*grid)[i][j] == '.' && roomMap[i][j] == room){
                    roomArea[count][0] = i;
                    roomArea[count][1] = j;
                    ++count;
                }
            }
        }

        // Place 1 furniture at a random spot.
        if(count > 0){ //Check if we've encountered at least one floor tile.
            int randSpot = rand() % count;
            int x = roomArea[randSpot][0];
            int y = roomArea[randSpot][1];
            (*grid)[x][y] = '@';
        }

        // Spawn the enemies in every room.
        enemyStats(enemy, dif);
        spawnEnemies(grid, rows, col, hero, enemy, roomArea, count);
    }
}

void freeGrid(char ***grid, int rows){
    for(int i = 0; i < rows; ++i){
        free((*grid)[i]);
    }
    free(*grid);
    *grid = NULL;
}

void drawVertical_TOP(char ***grid, int rows, int col, Walls wall[], int *count){

    // Values.
    *count = 0;
    int MIN_WALL_SPACE = (int)fmax(3.0, col * 0.1f), start = rand() % ((col / 3) - 1) + 3;
    int upperBound = (rows % 2 != 0 ? (int)(rows / 2) - 1 : (rows / 2) - 1);
    int lowerBound = (rows >= 8 ? 3 : 2);
    
    // Draw Walls.
    if(lowerBound > upperBound) return;
    for(int j = start; j < col - 3; j += MIN_WALL_SPACE){
        if(*count == 0 || rand() % 3 != 0){
            int wallHeight = rand() % (upperBound - lowerBound + 1) + lowerBound;
            for(int i = 1; i <= wallHeight; ++i){
                //(*grid)[i][j] = (rand() % WALL_CHANCE == 0 ? '.' : '#');
                (*grid)[i][j] = '#';
            }
            wall[*count].row = wallHeight;
            wall[*count].column = j;
            ++(*count);
        }
    }

    // Connect to the next wall.
    if(*count == 1) return;
    int prevCol = wall[0].column, prevRow = wall[0].row, curr = 1;
    for(int j = wall[curr].column; j <= wall[*count - 1].column; ++j){
        if(j == wall[curr].column){
            for(int k = wall[curr].row; k >= prevRow; --k){
                //(*grid)[k][prevCol] = (rand() % WALL_CHANCE == 0 ? '.' : '#');
                (*grid)[k][prevCol] = '#';
            }
            prevRow = wall[curr].row;
            prevCol = wall[curr].column;
            ++curr;
        }    
    }
}

void drawVertical_BOTTOM(char ***grid, int rows, int col, Walls wall[], int *count){

    // Values.
    *count = 0;
    int MIN_WALL_SPACE = (int)fmax(3.0, col * 0.1f), start = rand() % ((col / 3) - 1) + 3;
    int upperBound = (rows >= 9 ? rows - 4 : rows - 3);
    int lowerBound = (rows % 2 != 0 ? (rows + 1) / 2 : (rows / 2) + 1);
    
    // Draw Walls.
    if(lowerBound > upperBound) return;
    for(int j = start; j < col - 3; j += MIN_WALL_SPACE){
        if(*count == 0 || rand() % 3 != 0){
            int wallHeight = rand() % (upperBound - lowerBound + 1) + lowerBound;
            for(int i = wallHeight; i < rows - 1; ++i){
                //(*grid)[i][j] = (rand() % WALL_CHANCE == 0 ? '.' : '#');
                (*grid)[i][j] = '#';
            }
            wall[*count].row = wallHeight;
            wall[*count].column = j;
            ++(*count);
        }
    }
    
    // Connect to the next wall.
    if(*count == 1) return;
    int prevCol = wall[0].column, prevRow = wall[0].row, curr = 1;
    for(int j = wall[curr].column; j <= wall[*count - 1].column; ++j){
        if(j == wall[curr].column){
            for(int k = wall[curr].row; k < prevRow; ++k){
                //(*grid)[k][prevCol] = (rand() % WALL_CHANCE == 0 ? '.' : '#');
                (*grid)[k][prevCol] = '#';
            }
            prevRow = wall[curr].row;
            prevCol = wall[curr].column;
            ++curr;
        }    
    }
}

void drawHorizontal(char ***grid, int rows, int col, Walls wall[], int count){

    // Check if there are more than 2 walls, to avoid issues.
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

    // Connect the first column to the wall.
    for(int j = 0; j < wall[0].column; ++j){
        //(*grid)[wall[0].row][j] = (rand() % WALL_CHANCE == 0 ? '.' : '#');
        (*grid)[wall[0].row][j] = '#';
    }
    createDoor(grid, wall[0].row, wall[0].column - 1, 1);

    // Connect all the other columns.
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

    // Connect the last column to the wall.
    for(int j = wall[count - 1].column; j < col; ++j){
        //(*grid)[wall[count - 1].row][j] = (rand() % WALL_CHANCE == 0 ? '.' : '#');
        (*grid)[wall[count - 1].row][j] = '#';
    }
    createDoor(grid, wall[count - 1].row, col - 2, wall[count - 1].column + 1);
}

void createSG(char ***grid, int rows, int col, HeroData *hero, EnemyData *enemy, char dif[]){
    // Create the starting grid.
    int **roomMap = (int**)malloc(sizeof(int*) * rows);
    *grid = (char**)malloc(sizeof(char*) * rows);
    for(int i = 0; i < rows; ++i){
        (*grid)[i] = (char*)malloc(sizeof(char) * col);
        roomMap[i] = (int*)malloc(sizeof(int) * col);
        for(int j = 0; j < col; ++j){
            (*grid)[i][j] = (i == 0 || i == rows - 1 || j == 0 || j == col - 1 ? '#' : '.');
            roomMap[i][j] = -1;
        }
    }
    int count;
    countRooms(*grid, rows, col, &roomMap, &count);
    populateRooms(grid, rows, col, hero, enemy, roomMap, count, dif); // Generate at least 1 furniture per room.
    genFurniture(grid, rows, col); // Generate a couple more furniture.
    spawnHeroes(grid, rows, col, hero); // Place heroes and enemies
    
    // Free roomMap grid, can't use freeGrid, char not int
    for(int i = 0; i < rows; ++i){
        free(roomMap[i]);
    }
    free(roomMap);
}

void createGrid(char ***grid, int rows, int col, HeroData *hero, EnemyData *enemy, char dif[]){
    
    // Generating the grid for the next levels.
    int **roomMap = (int**)malloc(sizeof(int*) * rows);
    *grid = (char**)malloc(sizeof(char*) * rows);
    for(int i = 0; i < rows; ++i){
        (*grid)[i] = (char*)malloc(sizeof(char) * col);
        roomMap[i] = (int*)malloc(sizeof(int) * col);
        for(int j = 0; j < col; ++j){
            (*grid)[i][j] = (i == 0 || i == rows - 1 || j == 0 || j == col - 1 ? '#' : '.');
            roomMap[i][j] = -1;
        }
    }
    
    // Generating the upper walls.
    int countU = 0;
    Walls *upperWalls = malloc(sizeof(Walls) * col);
    drawVertical_TOP(grid, rows, col, upperWalls, &countU);
    drawHorizontal(grid, rows, col, upperWalls, countU);

    // Generating the lower walls.
    int countL = 0;
    Walls *lowerWalls = malloc(sizeof(Walls) * col);
    drawVertical_BOTTOM(grid, rows, col, lowerWalls, &countL);
    drawHorizontal(grid, rows, col, lowerWalls, countL);

    // Free walls
    free(upperWalls);
    free(lowerWalls);

    // Generate furniture, spawn players and enemies
    int count;
    createHallway(grid, rows, col);
    countRooms(*grid, rows, col, &roomMap, &count);
    populateRooms(grid, rows, col, hero, enemy, roomMap, count, dif); // Generate at least 1 furniture per room.
    genFurniture(grid, rows, col); // Generate a couple more furniture.
    clear_Rooms_Hallway(grid, rows, col);
    spawnHeroes(grid, rows, col, hero); // Place heroes and enemies
    
    // Free roomMap grid, can't use freeGrid, char not int
    for(int i = 0; i < rows; ++i){
        free(roomMap[i]);
    }
    free(roomMap);
    
    pause();
}

void printGrid(char ***grid, int rows, int col, HeroData hero, EnemyData enemy, char dif[], int level){

    // Using the largest number as the width specifier.
    int width = numberOfDig(rows);

    // Printing the grid.
    clearScreen();
    printf("\n==================================================\n");
    printf("                  DUNGEON ADVENTURE               \n");
    printf("==================================================\n\n");
    printf("-DIFFICULTY: %s\n-LEVEL: %d\n\n", dif, level);
    printf("--------------------------------------------------\n\n");
    printf("%*c", width + 1, ' ');
    for(int i = 0; i < col; ++i){
        printColChar(i, 2);
    }
    printf("\n");
    for(int i = 0; i < rows; ++i){
        printf("%*d ", width, i + 1);
        for(int j = 0; j < col; ++j){
            int isHero = 1;
            for(int k = 0; k < hero.numberOfHeroes; ++k){
                if(hero.data[k].x == i && hero.data[k].y == j){
                    printf("\033[0;32m");
                    printf("%2c ", (*grid)[i][j]);
                    printf("\033[0m");
                    isHero = 0;
                    break;
                }
            }
            if(!isHero) continue;
            int isEnemy = 1;
            for(int k = 0; k < enemy.totalEnemies; ++k){
                if(enemy.data[k].x == i && enemy.data[k].y == j){
                    printf("\033[0;31m");
                    printf("%2c ", (*grid)[i][j]);
                    printf("\033[0m");
                    isEnemy = 0;
                    break;
                }
            }
            if(!isEnemy) continue;
            if((*grid)[i][j] == '.'){
                printf("\033[0;33m");
                printf("%2c ", (*grid)[i][j]);
                printf("\033[0m");
                continue;
            }
            printf("%2c ", (*grid)[i][j]);
        }
        printf("\n");
    }
    printf("\n--------------------------------------------------\n\n");
    printf("Total Enemies: %d\n", enemy.totalEnemies);
    printf("\n--------------------------------------------------\n\n");
    printf("Hero Positions and Health:\n\n");
    for(int i = 0; i < hero.numberOfHeroes; ++i){
        printf(" > %c: %d, at %s\n", hero.data[i].class, hero.data[i].health, hero.data[i].positionChar);
    }
    printf("\n--------------------------------------------------\n");
}
