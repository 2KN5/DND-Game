#ifndef COMMON_FUNC_H
#define COMMON_FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "enemyStats.h"
#include "heroStats.h"

static inline void inputClosed(void){
    printf("\nInput stream closed. Exiting...\n");
    exit(EXIT_SUCCESS);
}

static inline void readLine(char buf[], int size){
    if(fgets(buf, size, stdin) == NULL) inputClosed();
}

/* The grid allocations were previously unchecked, so a failed malloc would
   have been dereferenced straight away. */
static inline void *checkedMalloc(size_t size){
    void *p = malloc(size);
    if(p == NULL){
        printf("\nOut of memory.\n");
        exit(EXIT_FAILURE);
    }
    return p;
}

static inline void pause(){
    printf("Press ENTER to continue...\n");
    if(getchar() == EOF) inputClosed();
}

static inline void returnColChar(int x, char str[]){
    if(x < 26){
        str[0] = 'A' + x;
        str[1] = '\0';
    } else if(x < 100){
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

static inline void shiftHeroes(HeroData *heroes, int index){
    for(int i = index; i < heroes->numberOfHeroes - 1; ++i){
        heroes->data[i] = heroes->data[i + 1];
    }
    --(heroes->numberOfHeroes);
}

static inline int check(char *choice){
    char buffer[100];
    readLine(buffer, sizeof(buffer));
    if(buffer[0] == '\0' || buffer[1] != '\n') return 0;
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
    if(c == EOF) inputClosed();
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