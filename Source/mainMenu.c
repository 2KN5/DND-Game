#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "mainMenu.h"

int validString(char c[]){
    if(c[strlen(c) - 1] != '\n'){
        clearBuffer();
        return 1;
    } else if(strlen(c) - 1 <= 4){
        return 1;
    } else {
        c[strlen(c) - 1] = '\0';
        return 0;
    }
}

void menu(HeroData *heroes, char dif[], int *exitGame){

    int n;
    char choice;
    clearScreen();

    // Keep asking the user, until they decide on their choices.
    while(1){

        // Assemble the party.
        char buffer[100] = {' '};
        while(buffer[0] != '\n'){
            printNOH();
            printf("Enter the number of heroes you wish to recruit (1-%d), or (%d) to Exit:\n>  ", MAX_PARTY_SIZE, MAX_PARTY_SIZE + 1);
            while(scanf("%d", &n) != 1 || n <= 0 || n > MAX_PARTY_SIZE + 1){
                clearScreen();
                printInvalidNOH();
                printf("Please enter a number between 1 and %d, or (%d) to Exit:\n> ", MAX_PARTY_SIZE, MAX_PARTY_SIZE + 1);
                clearBuffer();
            }
            fgets(buffer, sizeof(buffer), stdin);
            clearScreen();
        }
        if(n == MAX_PARTY_SIZE + 1){
            printf("\nExiting...\n");
            *exitGame = 1;
            return;
        }
        printf("\nPerfect! You chose %d heroes!\n", n);
        if(n != MAX_PARTY_SIZE){

            // Choose class for each hero.
            int partySize = 0;
            while(partySize < n){
                
                // Menu.
                char chooseClass[3]; 
                printChooseHeroes(n - partySize);
                fgets(chooseClass, sizeof(chooseClass), stdin);
                clearScreen();

                // Checking if user entered > 1 characters.
                if(chooseClass[strlen(chooseClass) - 1] != '\n'){
                    printf("You can only input a character!\n\n");
                    clearBuffer();
                    continue;
                } else {
                    chooseClass[strlen(chooseClass) - 1] = '\0';
                }
        
                // Check for duplicates and valid choices.
                upperString(chooseClass);
                if(strcmp(chooseClass, "B") != 0 && strcmp(chooseClass, "D") != 0 && strcmp(chooseClass, "E") != 0 && strcmp(chooseClass, "W") != 0 && strcmp(chooseClass, "H") != 0){
                    printf("\nInvalid Choice!\n");
                    continue;
                }
                int dup = 0;
                for(int i = 0; i < partySize; ++i){
                    if(chooseClass[0] == heroes->data[i].class){
                        dup = 1;
                        break;
                    }
                }
                if(dup){
                    printf("\nYou've already selected a (%c) hero! Choose a different class.\n", chooseClass[0]);
                } else {
                    heroes->data[partySize].class = chooseClass[0];
                    ++(partySize);
                }
            }
            heroes->numberOfHeroes = partySize;
        } else {
            // If player selected MAX_PARTY_SIZE, initiate their values.
            heroes->data[0].class = 'B';
            heroes->data[1].class = 'W';
            heroes->data[2].class = 'E';
            heroes->data[3].class = 'D';
            heroes->data[4].class = 'H';
            heroes->numberOfHeroes = MAX_PARTY_SIZE;
        }
        
        // Set difficulty.
        while(1){
            printDifficulty();
            fgets(dif, 10, stdin);
            clearScreen();

            // Check if value entered has a valid length.
            if(dif[strlen(dif) - 1] != '\n'){
                clearBuffer();
            } else {
                dif[strlen(dif) - 1] = '\0';
            }

            // Convert to upper and compare.
            upperString(dif);
            if(strcmp(dif, "EASY") != 0 && strcmp(dif, "MEDIUM") != 0 && strcmp(dif, "HARD") != 0){
                printf("\n\nEnter a valid difficulty! -> (Easy, Medium, Hard)\n");
                continue;
            }
            break;
        }
        heroStats(heroes);
        printChoices(heroes, dif, &choice, heroes->numberOfHeroes);
        clearScreen();
        if(choice == 'Y') return;
    }
}