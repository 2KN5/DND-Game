#ifndef COMMON_FUNC_H
#define COMMON_FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

static inline void returnColChar(int x, char str[]){
    if(x < 26){
        str[0] = 'A' + x;
        str[1] = '\0';
    } else if(x <= 100){
        str[0] = 'A' + x / 26 - 1;
        str[1] = 'A' + x % 26;
        str[2] = '\0';
    } 
}

static inline void shiftEnemies(EnemyData *enemies, int index){
    for(int i = index; i < enemies->totalEnemies - 1; ++i){
        enemies->data[i] = enemies->data[i + 1];
    }
    --(enemies->totalEnemies);
}

static inline int check(char *choice){
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
    if(buffer[1] != '\n') return 0;
    *choice = toupper(buffer[0]);
    return (*choice == 'N' || *choice == 'Y' ? 1 : 0);
}

static inline void upperString(char *str){
    for(int i = 0; str[i] != '\0'; ++i){
        str[i] = toupper(str[i]);
    }
}

static inline void clearBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

static inline int roll(){
    return rand() % 6 + 1;
}

static inline void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


#endif