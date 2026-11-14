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
    printf("  # - Wall (Impassable)\n");
    printf("  . - Empty tile\n");
    printf("  @ - Furniture (Obstacle)\n");
    printf("  B/D/E/W/H - Heroes (Barbarian, Dwarf, Elf, Wizard, Healer)\n");
    printf("  1-9 - Enemies (Value = Remaining health)\n\n");

    printf("Hero Classes:\n");
    printf("  B: Barbarian | Health: 8  | Movement: 8 tiles   | Role: Frontline melee attacker\n");
    printf("  D: Dwarf     | Health: 7  | Movement: 6 tiles   | Role: Melee with diagonal strikes\n");
    printf("  E: Elf       | Health: 6  | Movement: 12 tiles  | Role: Ranged attacker (No adjacent targets)\n");
    printf("  W: Wizard    | Health: 4  | Movement: 10 tiles  | Role: Ranged attacker (Ignores obstacles)\n");
    printf("  H: Healer    | Health: 12 | Movement: 4 tiles   | Role: Restores health to allies (Cannot attack)\n\n");

    printf("Turn Structure:\n");
    printf("  - Each hero gets 2 actions (move + attack) per turn.\n");
    printf("  - Heroes can't move through walls, furniture, or enemies.\n");
    printf("  - When all heroes use their actions, enemies take their turn.\n\n");

    printf("Combat Rules:\n");
    printf("  - B: Melee only (Adjacent tile)\n");
    printf("  - D: Melee + Diagonal\n");
    printf("  - E: Ranged (Line-of-sight without adjacent tiles)\n");
    printf("  - W: Ranged (Ignores obstacles)\n");
    printf("  - H: Ranged, Up to 5 Tiles (Ignores obstacles)\n\n");

    printf("Dice Rolls:\n");
    printf("  - Heroes roll 3 dice when attacking, enemies roll 2.\n");
    printf("  - Defense: all roll 2 dice.\n");
    printf("  - Dice outcomes:\n");
    printf("       - Skull (Damage)\n");
    printf("       - White Shield (Hero Defense)\n");
    printf("       - Black Shield (Enemy Defense)\n\n");

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

    printf("Choose your champions (1 to %d heroes):\n", MAX_PARTY_SIZE);
    printf("  B - Barbarian: Mighty and fearless, a juggernaut of melee combat.\n");
    printf("  D - Dwarf: Sturdy and resilient, strikes from unexpected angles.\n");
    printf("  E - Elf: Agile and precise, deadly with ranged attacks.\n");
    printf("  W - Wizard: Wise and powerful, commands arcane forces from afar.\n");
    printf("  H - Healer: Compassionate and vital, restores allies' strength amidst chaos.\n\n");
}

void printInvalidNOH(){
    printf("\nInvalid selection!\n\n");
    printf("You may only choose up to 4 unique heroes for your party.\n");
}

void printChooseHeroes(int remainingHeroes){
    printf("\nHeroes left to choose: %d\n\n", remainingHeroes);
    printf("(B) Barbarian, (D) Dwarf, (E) Elf, (W) Wizard, (H) Healer\n");
    printf("Select a hero type -> ( B / D / E / W / H): ");
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

void mapRestrictions(){
    printf("\n==================================================\n");
    printf("                   MAP RESTRICTIONS               \n");
    printf("==================================================\n");
    printf("\n- Maximum map size is: 100 x 100.");
    printf("\n- The map must be at least 10 x 10 in size. (Recommended)\n");
    printf("- Size must allow enough space for all heroes, enemies, and furniture.\n\n");
    printf("Enter map size (N x M): ");
}

void readMapRestrictions(int *rows, int *col){
    char buffer[100] = {' '};
    while(buffer[0] != '\n'){
        clearScreen();
        mapRestrictions();
        while(scanf("%d%d", rows, col) != 2 || *rows < MIN_GRID_SIZE || *rows > MAX_GRID_SIZE || *col < MIN_GRID_SIZE || *col > MAX_GRID_SIZE){
            clearScreen();
            mapRestrictions();
            clearBuffer();
        }
        fgets(buffer, sizeof(buffer), stdin);
    } 
}

void gameSettings(HeroData heroes, char str[], int noh){
    clearScreen();
    printf("\n==================================================\n");
    printf("                    GAME SETTINGS                 \n");
    printf("==================================================\n");
    printf("\nDIFFICULTY         : %s\nYOUR PARTY INVOLVES: ", str);
    for(int i = 0; i < noh; ++i){
        printf("%c ", heroes.data[i].class);
    }
    printf("\n\nAre you ready to begin your adventure? (Y/N): Y\n");
    printf("\n--------------------------------------------------\n");
}

void asking(HeroData heroes, char str[], int pSize){
    char show;
    gameSettings(heroes, str, pSize);
    while(1){
        printf("\nWould you like to review your heroes' abilities before you begin? (Y/N)\n> ");
        if(!check(&show)){
            clearScreen();
            gameSettings(heroes, str, pSize);
            printf("\nPardon? Please enter (Y/N) to proceed.\n");
            continue;
        }
        clearScreen();
        printf("\n");
        if(show == 'Y'){
            for(int i = 0; i < pSize; i++){   
                printf("------------------------------------------------------------------\n");
                printf(" > Class    : %c\n", heroes.data[i].class);
                printf(" > HP       : %d\n", heroes.data[i].health);
                printf(" > Movement : %d tiles per turn\n", heroes.data[i].numberOfMoves);
                printf(" > Ability  : ");
                if(heroes.data[i].class == 'B'){
                    printf("High health and mobility, but no ranged attack.\n");
                    printf("              Steel and rage. Nothing more, nothing less.\n");
                } else if(heroes.data[i].class == 'D'){
                    printf("Attacks enemies even in diagonal tiles with his axe.\n");
                    printf("              Short in stature, tall in fury.\n");
                } else if(heroes.data[i].class == 'E'){
                    printf("Snipes enemies from afar, but can't hit what's adjacent.\n");
                    printf("              A leaf on the wind. An arrow in your heart.\n");
                } else if(heroes.data[i].class == 'H'){
                    printf("Restores health to nearby allies instead of dealing damage.\n");
                    printf("              A beacon of hope in the darkest depths.\n");
                } else if(heroes.data[i].class == 'W'){
                    printf("Can strike through walls and enemies with magic.\n");
                    printf("              He sees what others fear to imagine.\n");
                }
            }
            break;
        } else if(show == 'N'){
            clearScreen();
            gameSettings(heroes, str, pSize);
            printf("\nVery well. Let the journey unfold!\n\n");
            break;
        }
    }
    printf("------------------------------------------------------------------\n\n");
    pause();
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
            asking(*heroes, str, noh);
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

void allHeroesDead(int score){
    printf("\n==================================================\n");
    printf("                 YOUR PARTY HAS FALLEN\n");
    printf("==================================================\n");
    printf("\nThe dungeon claims another set of brave souls...\n");
    printf("Final Score: %d\n", score);
    printf("\nBetter luck next time, adventurer.\n");
}

void playerQuit(int score){
    printf("\n==================================================\n");
    printf("               YOU HAVE LEFT THE DUNGEON\n");
    printf("==================================================\n");
    printf("\nYou've chosen to abandon your quest.\n");
    printf("Final Score: %d\n", score);
    printf("\nSometimes, retreat is the better part of valor.\n");
}