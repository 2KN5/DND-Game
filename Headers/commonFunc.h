#ifndef COMMON_FUNC_H
#define COMMON_FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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