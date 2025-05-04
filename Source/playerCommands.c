#include <stdio.h>
#include <stdlib.h>
#include "playerCommands.h"

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
        return (choice == 'N' ? -1 : 1);
    }
    return 2;
}

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

int checkAttack(char attack[], int length){
    int curr = 3;
    if(attack[curr] == '*' && attack[curr - 1] != 'A') return 0;
    return 1;
}

int checkValidMoves(char moves[], int length, Hero hero){
    char validMoves[] = "UDLR";
    int currMove = 2, totalMoves = 0;

    // Check if it's a valid move, followed by a number.
    if(isalpha(moves[length])) return 0;
    while(currMove <= length){
        int count = 0;
        char str[3] = "\0";
        if(!strchr(validMoves, moves[currMove])) return 0;
        if(isalpha(moves[currMove + 1])) return 0;
        ++currMove;
        while(currMove <= length && isdigit(moves[currMove])){
            str[count] = moves[currMove];
            ++currMove; ++count;
        }
        totalMoves += atoi(str);
    }
    if(totalMoves > hero.numberOfMoves){
        printf("\nMax number of moves for that hero is - %d\n\n", hero.numberOfMoves);
        system("PAUSE");
        return 0;
    }
    return 1;
}

void updatePositionChar(int x, int y, char pos[]){
    char numbers[3];
    returnColChar(y, pos);
    sprintf(numbers, "%d", x);
    strcat(pos, "-");
    strcat(pos, numbers);
}

int applyMove(char ***grid, int rows, int col, char moves[], int length, Hero *hero){
    if(hero->actions[1]){
        int currMove = 2, prevX = hero->x, prevY = hero->y, numberOfActions = 0;
        char validMoves[] = "UDLR";
    
        while(currMove <= length){
            char str[3] = "\0", *ptr = strchr(validMoves, moves[currMove]);
            int count = 0, nom, index = ptr - validMoves;
    
            // Count number of steps.
            ++currMove;
            while(currMove <= length && isdigit(moves[currMove])){
                str[count] = moves[currMove];
                ++currMove; ++count;
            }
            nom = atoi(str); 
            
            // Checking direction.
            int step, newLoc;
            if(validMoves[index] == 'U' || validMoves[index] == 'D'){
                step = (validMoves[index] == 'D' ? 1 : -1), newLoc = hero->x + (step * nom);
                if(newLoc <= 0 || newLoc >= rows - 1){
                    printf("\nCan't go outside the map!\n\n");
                    system("PAUSE");
                    return 0;
                }
                for(int i = hero->x + step; i != newLoc + step; i += step){
                    if((*grid)[i][hero->y] != '.'){
                        printf("\nObstacle encountered!\n\n");
                        system("PAUSE");
                        if(numberOfActions) hero->actions[1] = 0;
                        return 0;
                    }
                }
                ++numberOfActions;
                hero->x = newLoc;
            } else {
                step = (validMoves[index] == 'R' ? 1 : -1), newLoc = hero->y + (step * nom);
                if(newLoc <= 0 || newLoc >= col - 1){
                    printf("\nCan't go outside the map!\n\n");
                    system("PAUSE");
                    return 0;
                }
                for(int j = hero->y + step; j != newLoc + step; j += step){
                    if((*grid)[hero->x][j] != '.'){
                        printf("\nObstacle encountered!\n\n");
                        system("PAUSE");
                        if(numberOfActions) hero->actions[1] = 0;
                        return 0;
                    }
                }
                ++numberOfActions;
                hero->y = newLoc;
            }
            (*grid)[prevX][prevY] = '.';
            prevX = hero->x; prevY = hero->y;
            (*grid)[hero->x][hero->y] = hero->class;
            updatePositionChar(hero->x + 1, hero->y, hero->positionChar);
        }
        hero->actions[1] = 0;
    } else {
        printf("\nYou have already moved this hero!\n\n");
        system("PAUSE");
        return 0;
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

void cdEnemy(char ***grid, int rows, int col, EnemyData *enemies, char dif[], int x, int y, char pos[]){
    if((*grid)[x][y] == '.'){
        spawnSingleEnemy(enemies, dif, x, y);
        (*grid)[x][y] = '0' + enemies->data[enemies->totalEnemies - 1].health;
        printf("\nSpawning enemy at position: %s\n\n", pos);
        system("PAUSE");
    } else {
        for(int i = 0; i < enemies->totalEnemies; ++i){
            if(enemies->data[i].x == x && enemies->data[i].y == y){
                (*grid)[x][y] = '.';
                shiftEnemies(enemies, i);
                printf("\nEliminating enemy at position: %s\n\n", pos);
                system("PAUSE");
                return;
            }
        }
        printf("\nYou can only Create/Destroy enemies!\n\n"); 
        system("PAUSE");
        return;
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
        return move[0];
    } else if(move[3] == '*'){
        return 'A';
    } else {
        return 'O';
    }
}

int getEnemyIndex(EnemyData enemies, int x, int y){
    int index = 0;
    for(int i = 0; i < enemies.totalEnemies; ++i){
        if(enemies.data[i].x == x && enemies.data[i].y == y){
            index = i;
            break;
        }
    }
    return index;
}

int getHeroIndex(HeroData heroes, char hero){
    int index = 0;
    for(int i = 0; i < heroes.numberOfHeroes; ++i){
        if(heroes.data[i].class == hero){
            index = i;
            break;
        }
    }
    return index;
}

int getCoords(char str[], int index, int rows, int col, int *x, int *y, char pos[]){
    char letters[3] = "", numbers[3] = "";
    int length = strlen(str) - 1, saveIndex = index - 1;

    // Get column coordinates.
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

    // Get row coordinates.
    int j = 0;
    while(index <= length && isdigit(str[index])){
        numbers[j] = str[index];
        pos[j + i] = numbers[j];
        ++index; ++j;
    }
    numbers[j] = '\0';
    *x = atoi(numbers) - 1;
    if(*x <= 0 || *x >= rows - 1) return 0;

    // Coordinates so I can print them later on.
    pos[j + i] = '\0';
    if(strlen(pos) != length - saveIndex) return 0;

    return 1;
}

int validCell(HeroData heroes, int x, int y, int index){

    int dx = abs(heroes.data[index].x - x);
    int dy = abs(heroes.data[index].y - y);

    if(heroes.data[index].class == 'B'){
        if(dx + dy == 1) return 1;
    } else if(heroes.data[index].class == 'D'){
        if(dx + dy >= 1 && (dx <= 1 && dy <= 1)) return 1;
    } else if(heroes.data[index].class == 'E'){
        if((dx == 0 && dy > 1) || (dy == 0 && dx > 1)) return 1;
    } else if(heroes.data[index].class == 'W'){
        if(dx + dy >= 1 && (dx == 0 || dy == 0)) return 1;
    }
    return 0;
}

int canAttack(char ***grid, int rows, int col, int enemyX, int enemyY, HeroData heroes, char move[], int index){
    if(isalpha((*grid)[enemyX][enemyY])){
        printf("\nYou can't attack your allies!\n\n");
        system("PAUSE");
        return 0;
    }
    if(!isdigit((*grid)[enemyX][enemyY])){
        printf("\nThat's not an enemy!\n\n");
        system("PAUSE");
        return 0;
    }
    if(heroes.data[index].class == 'W') return 1;
    int dx = heroes.data[index].x - enemyX;
    int dy = heroes.data[index].y - enemyY;

    // Checking attack validity for the elf, the others have been checked in validCell().
    int stepX = (dx < 0 ? 1 : -1), stepY = (dy < 0 ? 1 : -1);
    if(dx != 0){
        int newX = heroes.data[index].x + stepX;
        while(newX != enemyX){
            if((*grid)[newX][enemyY] != '.') return 0;
            newX += stepX;
        }
    }
    if(dy != 0){
        int newY = heroes.data[index].y + stepY;
        while(newY != enemyY){
            if((*grid)[enemyX][newY] != '.') return 0;
            newY += stepY;
        }
    }
    return 1;
}

int applyCommand(char ***grid, int rows, int col, HeroData *heroes, EnemyData *enemies, char dif[], char command, char move[]){
    int x, y, curr;
    int heroIndex = getHeroIndex(*heroes, move[0]);
    char position[6];

    if(command == 'M'){
        curr = 2;
        if(!getCoords(move, curr, rows, col, &x, &y, position)) return 0;
        cdEnemy(grid, rows, col, enemies, dif, x, y, position);
    } else if(command == 'A'){
        curr = 4;
        if(!getCoords(move, curr, rows, col, &x, &y, position)) return 0;
        if(!validCell(*heroes, x, y, heroIndex)) return 0;
        if(!canAttack(grid, rows, col, x, y, *heroes, move, heroIndex)) return 0;
        int enemyIndex = getEnemyIndex(*enemies, x, y);

        // Get damage and apply it to the enemy.
        printf("\nValid Attack at %s!\n\n", position);
        heroDamage(grid, x, y, &heroes->data[heroIndex], enemies, enemyIndex, position);
    } else {
        if(!checkValidMoves(move, strlen(move) - 1, heroes->data[heroIndex])) return 0;
        if(!applyMove(grid, rows, col, move, strlen(move) - 1, &heroes->data[heroIndex])) return 1;
        printf("\nValid Move!\n\n"); system("PAUSE");
    }
    return 1;
}