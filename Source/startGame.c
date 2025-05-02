#include <stdio.h>
#include <stdlib.h>
#include "startGame.h"

void playerActions(HeroData *heroes){
    int total = 0;
    for(int i = 0; i < heroes->numberOfHeroes; ++i){
        total += heroes->data[i].actions[0] + heroes->data[i].actions[1];
    }
    if(total == 0){
        for(int i = 0; i < heroes->numberOfHeroes; ++i){
            heroes->data[i].actions[0] = 1;
            heroes->data[i].actions[1] = 1;
        }
        printf("\nAll heroes have used their actions! Enemy turn begins...\n\n");
        system("PAUSE");
    }
}

int otherCommands(char c, char ***grid, int rows, int col, HeroData *heroes, EnemyData enemies, char dif[], int level){
    if(c == 'X'){
        for(int i = 0; i < heroes->numberOfHeroes; ++i){
            heroes->data[i].actions[0] = 1;
            heroes->data[i].actions[1] = 1;
        }
        printf("\nTurn ended! Let's see what the enemies are up to...\n\n");
        system("PAUSE");
        return 0;
    }
    if(c == 'Q'){
        char choice = 'N';
        while(1){
            printf("\nAre you sure you want to quit the game?\n(Y/N): ");
            if(!check(&choice)){
                printGrid(grid, rows, col, *heroes, enemies, dif, level);
                printf("\nInvalid Choice!\n");
                continue;
            }
            break;
        } 
        return (choice == 'N' ? 0 : 1);
    }
    return 2;
}

void printDistance(char **grid, int rows, int col, HeroData heroes, EnemyData enemies){
    int maxEnemies = enemies.totalEnemies;
    int canSee[maxEnemies][2], count = 0;
    char whichHero[maxEnemies];

    // Finding the number of enemies with a character in their range.
    for(int i = 0; i < maxEnemies; ++i){
        int distance = 6, index = 0;
        for(int j = 0; j < heroes.numberOfHeroes; ++j){
            int dx = abs(heroes.data[j].x - enemies.data[i].x), dy = abs(heroes.data[j].y - enemies.data[i].y);
            if(dx + dy < distance){
                distance = dx + dy;
                index = j;
            }
        }

        // Storing the location of the enemies.
        if(distance <= 5){
            canSee[count][0] = enemies.data[i].x;
            canSee[count][1] = enemies.data[i].y;
            whichHero[count] = heroes.data[index].class;
            ++count;
        }
    }

    // Orfea edo kane to attack, apla na checkarei an einai adjacent dhladh x - 1, x + 1, ...
    // mporeis apla na xrhsimopoihseis to manhattan distance dhladh apla auto -> int dx = abs(heroes.data[j].x - enemies.data[i].x) kai meta gia to y
    // kai gia na einai apo dipla to athroisma tous dx + dy == 1
    // meta an einai kanto oste na aferei hp apo ton hroa pou einai dipla tou me to function sto enemyMove.c
    // apla na xereis an to trexeis den tha allaxoun ta kanonika values sto main programma(einai apla test function gia tora), ara an thes na deis an douleuei tote
    // prepei na kaneis print mhnumata MESA SE AUTO TO FUNCTION
    // oraia tora stamata na tros burger
    for(int i = 0; i < count; ++i){
        printf("%c - Distance: X: %d / Y: %d\n", whichHero[i], canSee[i][0] + 1, canSee[i][1]);
    }
    system("PAUSE");
}

void startGame(char ***grid, int rows, int col, HeroData *heroes, EnemyData *enemies, char dif[], int level){
    int nextCommand;
    char result, move[28];
    printGrid(grid, rows, col, *heroes, *enemies, dif, level);
    printf("\nWelcome to the dungeon Player!\nAre you ready for the adventure?\n");
    while(1){
        while(enemies->totalEnemies > 0){
            do{
                result = checkMove(grid, rows, col, *heroes, *enemies, move);
                if(result == 'I'){
                    printGrid(grid, rows, col, *heroes, *enemies, dif, level);
                    printf("\nInvalid Move!\n");
                }
            } while(result == 'I');
            nextCommand = otherCommands(result, grid, rows, col, heroes, *enemies, dif, level);
            if(nextCommand == 0){
                // Let the enemy play
                printDistance(*grid, rows, col, *heroes, *enemies);
                printGrid(grid, rows, col, *heroes, *enemies, dif, level);
                continue;
            } else if(nextCommand == 1){
                return;
            } else if(!applyCommand(grid, rows, col, heroes, enemies, dif, result, move)){
                printGrid(grid, rows, col, *heroes, *enemies, dif, level);
                printf("\nInvalid Move!\n");
                continue;
            }
            playerActions(heroes);
            printGrid(grid, rows, col, *heroes, *enemies, dif, level);
        }

        // Update the level, free the grid, and create a new one.
        ++level;
        printf("\nLevel Cleared! Moving to the next one...\n\n");
        freeGrid(grid, rows);

        // Create the new grid.
        rows += 4; col += 4;
        createGrid(grid, rows, col, heroes, enemies, dif);
        printGrid(grid, rows, col, *heroes, *enemies, dif, level);
    }
}
