#include <stdio.h>
#include <stdlib.h>
#include "playerCommands.h"

int checkAttack(char attack[], int length){
    int curr = 3;
    if(attack[curr] == '*' && attack[curr - 1] != 'A') return 0;
    return 1;
}

int checkValidMoves(char moves[], int length){

    //Check if it's an attack.
    int currMove = 2;
    if(moves[currMove] == 'A') return checkAttack(moves, length);

    //Check if it's a valid move, followed by a number.
    char validMoves[] = "UDLR";
    if(isalpha(moves[length])) return 0;
    while(currMove <= length){
        if(!strchr(validMoves, moves[currMove])) return 0;
        if(isalpha(moves[currMove + 1])) return 0;
        ++currMove;
        while(currMove <= length && !isalpha(moves[currMove])){
            if(ispunct(moves[currMove])) return 0;
            ++currMove;
        }
    }
    return 1;
}

int isHero(char c, HeroData heroes){
    for(int i = 0; i < heroes.numberOfHeroes; ++i){
        if(c == heroes.data[i].class){
            return 1;
        }
    }
    return 0;
}

int checkValidLetters(char command[], int length, HeroData heroes){
    if(command[0] == '\0') return 0;
    if(strchr("XQ", command[0]) && command[1] == '\0') return 1;
    if(!isHero(command[0], heroes) && command[0] != 'M') return 0;
    if(command[1] != '>' || length < 4) return 0;
    return 1;
}

int returnColNumber(char letters[]){
    int length = strlen(letters);
    if(length == 1){
        return (letters[0] - 'A');
    } else {
        int first = 26 * (letters[0] - 'A' + 1), second = (letters[1] - 'A');
        return (first + second);
    }
}

int getCords(char str[], int index, int rows, int col, int *x, int *y, char pos[]){
    char letters[3] = "", numbers[3] = "";
    int length = strlen(str) - 1;

    //Get column coordinates.
    int i = 0;
    while(index <= length && isalpha(str[index])){
        letters[i] = str[index];
        pos[i] = letters[i];
        ++index; ++i;
    }
    letters[i] = '\0';
    *y = returnColNumber(letters);
    if(strlen(letters) < 1 || strlen(letters) > 2) return 0;
    if(*y <= 0 || *y >= col - 1) return 0;

    //Get row coordinates.
    int j = 0;
    while(index <= length && isdigit(str[index])){
        numbers[j] = str[index];
        pos[j + i] = numbers[j];
        ++index; ++j;
    }
    numbers[j] = '\0';
    *x = atoi(numbers) - 1;
    if(*x <= 0 || *x >= rows - 1) return 0;
    
    //Coordinates so I can print them later on.
    pos[j + i] = '\0';
    return 1;
}

void shiftEnemies(EnemyData *enemies, int index){
    for(int i = index; i < enemies->totalEnemies - 1; ++i){
        enemies->data[i] = enemies->data[i + 1];
    }
    --(enemies->totalEnemies);
}

void cdEnemy(char ***grid, int rows, int col, EnemyData *enemies, char dif[], int x, int y, char pos[]){
    if((*grid)[x][y] == '.'){
        spawnSingleEnemy(enemies, dif, x, y);
        (*grid)[x][y] = '0' + enemies->data[enemies->totalEnemies - 1].health;
        printf("Spawning enemy at position: %s\n", pos);
        system("PAUSE");
    } else {
        for(int i = 0; i < enemies->totalEnemies; ++i){
            if(enemies->data[i].x == x && enemies->data[i].y == y){
                (*grid)[x][y] = '.';
                shiftEnemies(enemies, i);
                printf("Eliminating enemy at position: %s\n", pos);
                system("PAUSE");
                return;
            }
        }
    }
}

int checkString(char str[], int length, HeroData heroes){
    if(str[length] != '\n'){
        clearBuffer();
        return 0;
    } else {
        upperString(str);
        str[length] = '\0';
        if(!checkValidLetters(str, length, heroes)) return 0;
        if(isHero(str[0], heroes) && !checkAttack(str, length - 1)) return 0;
        return 1;
    }
}

char checkMove(char ***grid, int rows, int col, HeroData heroes, EnemyData enemies, char move[]){
    printf("\nMake your move: ");
    fgets(move, 28, stdin);
    int length = strlen(move) - 1;
    if(!checkString(move, length, heroes)){
        return 'I';
    }
    if(move[0] == 'M' || move[0] == 'X' || move[0] == 'Q'){
        printf("Valid Command!\n");
        system("PAUSE");
        return move[0];
    } else if(move[3] == '*'){
        printf("Valid Attack!\n");
        system("PAUSE");
        return 'A';
    } else {
        printf("Valid Move!\n");
        system("PAUSE");
        return 'O';
    }
}

int applyMove(char ***grid, int rows, int col, HeroData *heroes, EnemyData *enemies, char dif[], char command, char move[]){
    int x, y;
    char position[6];
    if(command == 'M'){
        int curr = 2;
        if(!getCords(move, curr, rows, col, &x, &y, position)) return 0;
        cdEnemy(grid, rows, col, enemies, dif, x, y, position);
    } else if(command == 'A'){
        return 1;
    } else {
        return 2;
    }
    return 3;
}