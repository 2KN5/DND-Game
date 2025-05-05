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

void menu(HeroData *hero, char dif[], int *exitGame){

    int n;
    char choice;
    clearScreen();

    // Keep asking the user, until they decide on their choices.
    while(1){

        // Assemble the party.
        char buffer[100] = {' '};
        while(buffer[0] != '\n'){
            printNOH();
            printf("Enter the number of heroes you wish to recruit (1-%d), or (5) to Exit:\n>  ", MAX_PARTY_SIZE);
            while(scanf("%d", &n) != 1 || n <= 0 || n > MAX_PARTY_SIZE + 1){
                clearScreen();
                printInvalidNOH();
                printf("Please enter a number between 1 and 4, or (5) to Exit:\n> ");
                clearBuffer();
            }
            fgets(buffer, sizeof(buffer), stdin);
            clearScreen();
        }
        if(n == 5){
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
                if(strcmp(chooseClass, "B") != 0 && strcmp(chooseClass, "D") != 0 && strcmp(chooseClass, "E") != 0 && strcmp(chooseClass, "W") != 0){
                    printf("\nInvalid Choice!\n");
                    continue;
                }
                int dup = 0;
                for(int i = 0; i < partySize; ++i){
                    if(chooseClass[0] == hero->data[i].class){
                        dup = 1;
                        break;
                    }
                }
                if(dup){
                    printf("\nYou've already selected a (%c) hero! Choose a different class.\n", chooseClass[0]);
                } else {
                    hero->data[partySize].class = chooseClass[0];
                    ++(partySize);
                }
            }
            hero->numberOfHeroes = partySize;
        } else {
            // If player selected 4, initiate their values.
            hero->data[0].class = 'B';
            hero->data[1].class = 'W';
            hero->data[2].class = 'E';
            hero->data[3].class = 'D';
            hero->numberOfHeroes = 4;
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
                printf("\nEnter a valid difficulty! -> (Easy, Medium, Hard)\n");
                continue;
            }
            break;
        }
        printChoices(hero, dif, &choice, hero->numberOfHeroes);
        clearScreen();
        if(choice == 'Y') return;
    }
}