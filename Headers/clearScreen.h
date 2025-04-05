#ifndef CLEAR_SCREEN_H
#define CLEAR_SCREEN_H

#include <stdlib.h>
#include <time.h>

static inline int clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

#endif