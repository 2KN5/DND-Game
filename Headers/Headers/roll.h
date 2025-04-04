#ifndef ROLL_H
#define ROLL_H

#include <stdlib.h>
#include <time.h>

static inline int roll(){
    return rand() % 6 + 1;
}

#endif