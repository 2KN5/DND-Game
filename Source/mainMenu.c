#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <mainMenu.h>
#include "heroStats.h"

void clearBuffer(){
    int c, i = 0;
    while((c = getchar()) != '\n' && c != EOF){
        if(i == 0){
            printf("-Removing extra characters..\n");
            ++i;
        }
    }
}

void upperString(char *str){
    for(int i = 0; str[i] != '\0'; ++i){
        str[i] = toupper(str[i]);
    }
}

void printChoices(char *str, struct Hero h[], int noh){
    printf("GAME SETTINGS\n\n");
    printf("DIFFICULTY: %s\nYOUR PARTY INVOLVES: ", str);
    for(int i = 0; i < noh; ++i){
        printf("%c ", h[i].class);
    }
    printf("\n\nAre you ready to begin?\n");
    system("PAUSE");
    system("cls");
}

void menu(struct Hero hero[MAX_PARTY_SIZE], int *partySize, char dif[]){

    //Initiate party size.
    int n;
    printf("Welcome to the game!\n");
    printf("You may assemble a party of up to %d unique heroes (B/D/E/W).\n", MAX_PARTY_SIZE);
    printf("Enter number of heroes (0-%d): ", MAX_PARTY_SIZE);
    scanf("%d", &n);
    while(n < 0 || n > MAX_PARTY_SIZE){
        printf("Invalid party size! You may only bring 0-%d heroes.\n", MAX_PARTY_SIZE);
        printf("Try again, adventurer (0-%d): ", MAX_PARTY_SIZE);
        scanf("%d", &n);
    }
    system("cls");
    clearBuffer(); // Clear input buffer
    printf("Perfect! You chose %d heroes!\n", n);
    
    //Choose class for each hero.
    *partySize = 0;
    while(*partySize < n){
        
        char chooseClass[3]; 
        printf("(B) Barbarian, (D) Dwarf, (E) Elf, (W) Wizard.\n");
        printf("Select a hero type -> ( B / D / E / W): ");
        fgets(chooseClass, 3, stdin);
        system("cls");
        if(chooseClass[strlen(chooseClass) - 1] != '\n'){
            printf("You can only input a character!\n");
            printf("%c\n", chooseClass[strlen(chooseClass) - 1]);
            clearBuffer();
            continue;
        } else {
            chooseClass[strlen(chooseClass) - 1] = '\0';
        }
        
        system("cls");

        //Check for duplicates and valid choices.
        if(!isalpha(chooseClass[0])){
            printf("Valid choices are ");
            continue;
        }
        upperString(chooseClass);
        if(strcmp(chooseClass, "B") != 0 && strcmp(chooseClass, "D") != 0 && strcmp(chooseClass, "E") != 0 && strcmp(chooseClass, "W") != 0){
            printf("Valid choices are ");
            continue;
        }
        int dup = 0;
        for(int i = 0; i < *partySize; ++i){
            if(chooseClass[0] == hero[i].class){
                dup = 1;
                break;
            }
        }
        if(dup){
            printf("You've already selected a (%c) hero! Choose a different class.\n", chooseClass[0]);
        } else {
            hero[*partySize].class = chooseClass[0];
            ++(*partySize);
        }
    }

    //Set difficulty.
    printf("Choose the difficulty -> (Easy, Medium, Hard): ");
    while(1){
        fgets(dif, 8, stdin);
        system("cls");
        if(dif[strlen(dif) - 1] != '\n'){
            clearBuffer();
        } else {
            dif[strlen(dif) - 1] = '\0';
        }
        upperString(dif);
        if(strcmp(dif, "EASY") != 0 && strcmp(dif, "MEDIUM") != 0 && strcmp(dif, "HARD") != 0){
            printf("Choose a valid difficulty -> (Easy, Medium, Hard): ");
            continue;
        }
        break;
    }
    system("cls");
    printChoices(dif, hero, n);
}