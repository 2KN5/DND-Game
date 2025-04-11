#include <stdio.h>
#include <stdlib.h>
#include "playerCommands.h"

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

int checkAttack(char attack[], int length){
    int curr = 3;
    if(attack[curr] == '*' && (attack[curr - 1] != 'A' || attack[0] == 'M')) return 0;
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
    if(command[1] != '>' || command[1] == '>' && length < 4) return 0;
    return 1;
}

int checkString(char str[], int length, HeroData heroes){
    upperString(str);
    if(str[length] != '\n'){
        clearBuffer();
        return 0;
    } else {
        str[length] = '\0';
        if(!checkValidLetters(str, length, heroes)) return 0;
        return checkAttack(str, length - 1);
        return 1;
    }
}

char checkMove(char ***grid, int rows, int col, HeroData heroes, EnemyData enemies){
    char move[28];
    printf("\nMake your move: ");
    fgets(move, sizeof(move), stdin);
    int length = strlen(move) - 1;
    if(!checkString(move, length, heroes)){
        return 'I';
    }
    if(move[0] == 'M' || move[0] == 'X' || move[0] == 'Q'){
        return move[0];
    } else if(move[3] == '*'){
        return 'A';
    } else {
        return 'O';
    }
}

void applyMove(char ***grid, int rows, int col, HeroData *heroes, EnemyData *enemies, char move){
    
}