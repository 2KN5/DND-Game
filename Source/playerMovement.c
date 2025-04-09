#include <stdio.h>
#include <stdlib.h>
#include "playerMovement.h"

int checkValidLetter(){

}

int checkString(char move[], int length, Hero hero[]){
    upperString(move);
    if(move[length] != '\n' || length < 4){
        if(move[length] != '\n') clearBuffer();
        return 0;
    } else {
        move[length - 1] = '\0';
        int f = 0;
        for(int i = 0; i < hero->numberOfHeroes; ++i){
            if(move[0] == hero[i].class){
                f = 1;
                break;
            }
        } 
        if(!f || move[1] != '>') return 0;
        checkValidLetter(); // Check if the letters after > are valid UDLR, and if number follow right after those (valid)letters
        return 1;
    }
}

int makeMove(char ***grid, int rows, int col, Hero hero[], Enemy enemy[]){
    char move[28];
    printf("Make your move: ");
    fgets(move, sizeof(move), stdin);
    int length = strlen(move) - 1;
    if(!checkString(move, length, hero)){
        return 0;
    }
    return 1;
}

