#include <stdio.h>
#include <stdlib.h>
#include "printStatements.h"

void gameInstructions(){
    clearScreen();
    printf("\n\n");
    printf("Welcome to the Dungeon of Zargon!\n");
    printf("Your quest begins now. Defeat all enemies and survive through each floor.\n\n");

    printf("Game Instructions\n");
    printf("---------------------------------------------------------------------\n");
    printf("Objective: Defeat all monsters on each level to progress.\n");
    printf("Grid Legend:\n");
    printf("  # - Wall (impassable)\n");
    printf("  . - Empty tile\n");
    printf("  @ - Furniture (obstacle)\n");
    printf("  B/D/E/W - Heroes (Barbarian, Dwarf, Elf, Wizard)\n");
    printf("  1-9 - Enemies (value = remaining health)\n\n");

    printf("Hero Classes:\n");
    printf("  B: Barbarian | Health: 8 | Movement: 8 tiles\n");
    printf("  D: Dwarf     | Health: 7 | Movement: 6 tiles\n");
    printf("  E: Elf       | Health: 6 | Movement: 12 tiles\n");
    printf("  W: Wizard    | Health: 4 | Movement: 10 tiles\n\n");

    printf("Turn Structure:\n");
    printf("  - Each hero gets 2 actions (move + attack) per turn.\n");
    printf("  - Heroes can't move through walls, furniture, or enemies.\n");
    printf("  - When all heroes use their actions, enemies take their turn.\n\n");

    printf("Combat Rules:\n");
    printf("  - B: Melee only (Adjacent tile)\n");
    printf("  - D: Melee + Diagonal\n");
    printf("  - E: Ranged (Line-of-sight without adjacent tiles)\n");
    printf("  - W: Ranged (Ignores obstacles)\n\n");

    printf("Dice Rolls:\n");
    printf("  - Heroes roll 3 dice when attacking, enemies roll 2.\n");
    printf("  - Defense: all roll 2 dice.\n");
    printf("  - Dice outcomes:\n");
    printf("       - Skull (damage)\n");
    printf("       - White Shield (hero defense)\n");
    printf("       - Black Shield (enemy defense)\n\n");

    printf("Commands:\n");
    printf("  B>L3U2   - Move Barbarian 3 Left, then 2 Up\n");
    printf("  E>A*D5   - Elf attacks position D5\n");
    printf("  M>D4     - Create or remove monster at D4 (Zargon command)\n");
    printf("  X        - End current player turn early\n");
    printf("  Q        - Quit the game\n");
    printf("---------------------------------------------------------------------\n\n");
    pause();
}

void printNOH(){
    printf("\nYou now stand at the gates of the dungeon...\n");
    printf("Assemble your party of brave heroes to face the dangers within.\n\n");

    printf("Choose your champions (1 to 4 heroes):\n");
    printf("  B - Barbarian: Mighty and fearless, a juggernaut of melee combat.\n");
    printf("  D - Dwarf: Sturdy and resilient, strikes from unexpected angles.\n");
    printf("  E - Elf: Agile and precise, deadly with ranged attacks.\n");
    printf("  W - Wizard: Wise and powerful, commands arcane forces from afar.\n\n");
}

void printInvalidNOH(){
    printf("\nInvalid selection!\n\n");
    printf("You may only choose up to 4 unique heroes for your party.\n");
}

void printChooseHeroes(int remainingHeroes){
    printf("\nHeroes left to choose: %d\n\n", remainingHeroes);
    printf("(B) Barbarian, (D) Dwarf, (E) Elf, (W) Wizard\n");
    printf("Select a hero type -> ( B / D / E / W ): ");
}

void printDifficulty(){
    printf("\n==================================================\n");
    printf("                CHOOSE YOUR CHALLENGE             \n");
    printf("==================================================\n");
    printf("\nSelect a difficulty level to begin your quest:\n\n");
    printf(" - Easy   : For beginners. Fewer enemies, more room to breathe.\n");
    printf(" - Medium : A balanced experience for seasoned adventurers.\n");
    printf(" - Hard   : Only the brave survive. Expect more enemies and tougher odds.\n\n");
    printf("Choose the difficulty -> (Easy / Medium / Hard): ");
}

void welcome(){
    printf("\nWelcome to the dungeon, brave adventurer!\n");
    printf("Are you ready for the challenge?\n\n");
    printf("--------------------------------------------------\n");
}

void clearHero(HeroData *heroes){
    for(int i = 0; i < MAX_PARTY_SIZE; ++i){
        heroes->data[i].class = ' ';
    }
    heroes->numberOfHeroes = 0;
}

void printChoices(HeroData *heroes, char str[], char *first, int noh){
    char second;
    while(1){

        // Always re-display settings.
        clearScreen();
        printf("\n==================================================\n");
        printf("                    GAME SETTINGS                 \n");
        printf("==================================================\n");
        printf("\nDIFFICULTY         : %s\nYOUR PARTY INVOLVES: ", str);
        for(int i = 0; i < noh; ++i){
            printf("%c ", heroes->data[i].class);
        }

        // First question: ...
        printf("\n\nAre you ready to begin your adventure? (Y/N): ");
        if(!check(first)) continue;
        clearScreen();
        if(*first == 'Y'){
            return; // Exit to starting menu.
        }

        // Second question: ...
        while(1){
            printf("\n==================================================\n");
            printf("                CURRENT GAME CHOICES              \n");
            printf("==================================================\n");
            printf("\nDIFFICULTY         : %s\nYOUR PARTY INVOLVES: ", str);
            for(int i = 0; i < noh; ++i){
                printf("%c ", heroes->data[i].class);
            }
            printf("\n\nWould you like to change your choices? (Y/N): ");
            if(!check(&second)){
                clearScreen();
                printf("\nInvalid Statement!\n\n");
                continue;
            }
            break;
        }
        if(second == 'Y'){ // Exit to the starting menu.
            clearHero(heroes);
            return;
        } 
    }
}

void mapRestrictions(){
    printf("\n==================================================\n");
    printf("                   MAP RESTRICTIONS               \n");
    printf("==================================================\n");
    printf("\n- The map must be at least 10 x 10 in size. (Suggested)\n");
    printf("- Maximum column width is 92 (Due to screen size).\n");
    printf("- Size must allow enough space for all heroes, enemies, and furniture.\n\n");
    printf("Enter map size (N x M): ");
}

void readMapRestrictions(int *rows, int *col){
    char buffer[100] = {' '};
    while(buffer[0] != '\n'){
        clearScreen();
        mapRestrictions();
        while(scanf("%d%d", rows, col) != 2 || *rows < 10 || *col < 10 || *col > 92){
            clearScreen();
            mapRestrictions();
            clearBuffer();
        }
        fgets(buffer, sizeof(buffer), stdin);
    } 
}