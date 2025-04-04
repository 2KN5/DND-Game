#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <mainMenu.h>
#include "heroStats.h"

void clearBuffer(){
    int c, i = 0;
    while((c = getchar()) != '\n' && c != EOF);
}

void upperString(char *str){
    for(int i = 0; str[i] != '\0'; ++i){
        str[i] = toupper(str[i]);
    }
}

int check(char *choice){
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
    if(buffer[1] != '\n') return 0;
    *choice = toupper(buffer[0]);
    return (*choice == 'N' || *choice == 'Y' ? 1 : 0);
}

void clearHero(struct Hero h[MAX_PARTY_SIZE]){
    for(int i = 0; i < MAX_PARTY_SIZE; ++i){
        h[i].class = ' ';
    }
}

void printChoices(char *str, struct Hero h[], int noh, char *first){
    int f = 1;
    char second;
    while(1){
        //Always re-display settings.
        //if(!f) system("cls");
        printf("GAME SETTINGS\n\n");
        printf("DIFFICULTY: %s\nYOUR PARTY INVOLVES: ", str);
        for(int i = 0; i < noh; ++i){
            printf("%c ", h[i].class);
        }

        //First question: ...
        printf("\n\nAre you ready to begin? (Y/N): ");
        if(!check(first)) continue;
        if(*first == 'Y'){
            system("cls");
            return;
        }
        //Second question: ...
        system("cls");
        printf("Would you like to change your choices? (Y/N): ");
        if(!check(&second)){
            printf("Invalid Statement! (Y/N) - %c\n\n", second);
            f = 1;
            continue;
        }
        if(second == 'Y'){ //Exit to the starting menu
            system("cls");
            clearHero(h);
            return;
        } 
    }
}

void menu(struct Hero hero[MAX_PARTY_SIZE], int *partySize, char dif[]){

    //Initiate party size.
    int n;
    char choice;
    system("cls");
    printf("Welcome to the game!\n\n");

    //Keep asking the user, until they decide on their choices
    while(1){

        //Assemble the party.
        char buffer[100] = {' '};
        while(buffer[0] != '\n'){
            printf("You may assemble a party of up to %d unique heroes.\n\n", MAX_PARTY_SIZE);
            printf("Enter number of heroes (0-%d): ", MAX_PARTY_SIZE);
            while(scanf("%d", &n) != 1 || n < 0 || n > MAX_PARTY_SIZE){
                system("cls");
                printf("You may assemble a party of up to %d unique heroes.\n\n", MAX_PARTY_SIZE);
                printf("Enter number of heroes (0-%d): ", MAX_PARTY_SIZE);
                clearBuffer();
            }
            fgets(buffer, sizeof(buffer), stdin);
            system("cls");
        }
        printf("Perfect! You chose %d heroes!\n\n", n);

        if(n != MAX_PARTY_SIZE){

            //Choose class for each hero.
            *partySize = 0;
            while(*partySize < n){
                
                //Menu
                char chooseClass[3]; 
                printf("Heroes left: %d\n\n", n - *partySize);
                printf("(B) Barbarian, (D) Dwarf, (E) Elf, (W) Wizard.\n");
                printf("Select a hero type -> ( B / D / E / W): ");
                fgets(chooseClass, 3, stdin);
                system("cls");

                //Checking if user entered > 1 characters.
                if(chooseClass[strlen(chooseClass) - 1] != '\n'){
                    printf("You can only input a character!\n\n");
                    clearBuffer();
                    continue;
                } else {
                    chooseClass[strlen(chooseClass) - 1] = '\0';
                }
                system("cls");
        
                //Check for duplicates and valid choices.
                upperString(chooseClass);
                if(strcmp(chooseClass, "B") != 0 && strcmp(chooseClass, "D") != 0 && strcmp(chooseClass, "E") != 0 && strcmp(chooseClass, "W") != 0){
                    printf("Invalid Choice!\n\n");
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
                    printf("You've already selected a (%c) hero! Choose a different class.\n\n", chooseClass[0]);
                } else {
                    hero[*partySize].class = chooseClass[0];
                    ++(*partySize);
                }
            }
        } else {
            //If player selected 4, initiate their values.
            hero[0].class = 'B';
            hero[1].class = 'W';
            hero[2].class = 'E';
            hero[3].class = 'D';
            *partySize = 4;
        }

        //Set difficulty.
        printf("Choose the difficulty -> (Easy, Medium, Hard): ");
        while(1){
            fgets(dif, 8, stdin);
            system("cls");

            //Clear input buffer.
            if(dif[strlen(dif) - 1] != '\n'){
                clearBuffer();
            } else {
                dif[strlen(dif) - 1] = '\0';
            }

            //Convert to upper and compare.
            upperString(dif);
            if(strcmp(dif, "EASY") != 0 && strcmp(dif, "MEDIUM") != 0 && strcmp(dif, "HARD") != 0){
                printf("Choose a valid difficulty -> (Easy, Medium, Hard): ");
                continue;
            }
            break;
        }
        printChoices(dif, hero, n, &choice);
        if(choice == 'Y') return;
    }
}