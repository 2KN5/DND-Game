#include <stdio.h>
#include <stdlib.h>
#include "enemyTurn.h"

int isValidTile(char **grid, int rows, int col, int x, int y, int visited[rows][col]){
    return (((x >= 1 && x < rows - 1) && (y >= 1 && y < col - 1) &&
            (grid[x][y] == '.' || isalpha(grid[x][y])) && 
            visited[x][y] == 1) ? 1 : 0);
}

int findPath(char **grid, int rows, int col, int enemyX, int enemyY, int heroX, int heroY, int *pathLength, Point path[]){
    const int dx[] = {-1, 1, 0, 0}; // UP, DOWN 
    const int dy[] = {0, 0, -1, 1}; // LEFT, RIGHT
    int visited[rows][col];
    Point parent[rows][col];

    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < col; ++j){
            visited[i][j] = 0;
            parent[i][j].x = -1;
            parent[i][j].y = -1;
        }
    }

    // Initializing the queue.
    Point queue[rows * col];
    int front = 0, rear = 0;
    queue[rear].x = enemyX;
    queue[rear].y = enemyY;
    ++rear;
    visited[enemyX][enemyY] = 1;
    
    // BFS Loop
    while(front < rear){
        Point current = queue[front]; // Queue[front] x and y.
        for(int i = 0; i < 4; ++i){
            int newX = current.x + dx[i];
            int newY = current.y + dy[i];
            if(isValidTile(grid, rows, col, newX, newY, visited)){
                queue[rear].x = newX;
                queue[rear].y = newY;
                ++rear;
                visited[newX][newY] = 1;
                parent[newX][newY] = current; // Current x and y. 
            }
        }
        ++front;
    }
    if(!visited[heroX][heroY]){
        printf("No path found!\n");
        return 0;
    }
    for(int i = heroX; i <= 0; --i){
        
    }
}

void enemyTurn(char ***grid, int rows, int col, HeroData *heroes, EnemyData enemies){
    int maxEnemies = enemies.totalEnemies;
    int canSee[maxEnemies][2], count = 0;
    char whichHero[maxEnemies];

    // Finding the number of enemies with a character in their range.
    for(int i = 0; i < maxEnemies; ++i){
        int distance = 6, index = 0;
        for(int j = 0; j < heroes->numberOfHeroes; ++j){
            int dx = abs(heroes->data[j].x - enemies.data[i].x), dy = abs(heroes->data[j].y - enemies.data[i].y);
            if(dx + dy < distance){
                distance = dx + dy;
                index = j;
            }
        }

        // Storing the location of the enemies.
        if(distance <= 5){
            canSee[count][0] = enemies.data[i].x;
            canSee[count][1] = enemies.data[i].y;
            whichHero[count] = heroes->data[index].class;
            ++count;
        }
    }

    for(int i = 0; i < count; ++i){
        int index;
        for(int j = 0; j < heroes->numberOfHeroes; ++j){
            if(heroes->data[j].class == whichHero[i]){
                index = j;
            }
        }
        int heroX = heroes->data[index].x, heroY = heroes->data[index].y;
        int enemyX = canSee[i][0], enemyY = canSee[i][1];
        int dx = abs(heroX - enemyX), dy = abs(heroY - enemyY);
        if(dx + dy == 1){
            printf("In range!\n");
            enemyDamage(grid, heroX, heroY, heroes, index);
        } else {
            printf("Enemy at (%d, %c) is targetting (%c) with %d Health!\n", enemyX + 1, enemyY + 65, whichHero[i], heroes->data[index].health);
            printf("Not in range, time to move!\n");
        }
    }
    system("PAUSE");
}