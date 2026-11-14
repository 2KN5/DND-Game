# DND-Game

A turn-based dungeon crawler for the terminal, written in C with no external
dependencies. Procedurally generates a new dungeon every level, with walls,
rooms and doors carved out by the generator, and enemies that path toward your
party using breadth-first search.

```
==================================================
                  DUNGEON ADVENTURE
==================================================

-DIFFICULTY: MEDIUM
-LEVEL: 2

--------------------------------------------------

    A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z  AA AB AC
 1  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #
 2  #  .  6  .  .  #  .  .  #  .  .  #  .  6  #  .  .  #  .  .  .  @  .  .  .  .  .  .  #
 3  #  @  .  .  .  #  6  @  #  .  @  #  4  @  #  .  .  #  .  .  .  .  .  .  .  .  .  .  #
 4  #  .  .  .  .  #  .  5  #  6  .  #  .  4  #  .  .  #  .  .  .  B  .  .  .  .  .  .  #
 5  #  .  .  .  .  #  6  .  #  .  .  #  .  .  #  .  @  #  .  .  .  .  .  .  .  6  .  .  #
 6  #  .  .  .  .  #  .  4  #  .  .  #  .  #  #  .  .  #  .  6  .  .  .  .  .  .  .  .  #
 7  #  .  .  .  .  #  .  #  #  6  H  #  .  .  #  .  4  #  .  .  .  .  .  .  .  .  .  .  #
 8  #  .  .  .  .  #  .  .  #  .  .  #  .  .  #  .  .  #  .  .  .  .  .  .  .  .  .  .  #
 9  #  .  .  .  .  #  .  .  #  #  .  #  @  .  #  .  #  #  #  #  .  #  #  #  #  #  #  #  #
10  #  #  #  #  .  #  .  6  .  @  .  6  5  5  .  .  4  5  @  .  .  5  6  .  5  @  .  4  #
11  #  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  #
12  #  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  #  .  #  #  .  6  .  .  .  @  .  @  #
13  #  .  @  .  .  .  .  .  .  .  .  6  .  #  #  .  #  .  4  #  4  .  #  #  .  #  .  #  #
14  #  4  .  .  .  .  .  .  .  .  .  .  .  #  .  .  #  .  .  #  @  .  #  .  .  #  .  .  #
15  #  .  .  .  .  .  .  @  .  .  .  .  E  #  .  .  #  .  5  #  #  .  #  @  .  #  6  .  #
16  #  .  .  .  .  .  .  .  .  .  .  .  .  #  .  @  #  .  .  #  4  .  #  .  .  #  .  @  #
17  #  .  #  #  #  #  .  #  #  #  #  #  #  #  5  .  #  .  .  #  5  5  #  5  5  #  6  .  #
18  #  .  @  4  #  .  .  6  .  .  .  6  .  #  .  .  #  @  .  #  @  .  #  @  .  #  .  .  #
19  #  .  5  6  #  .  .  4  .  .  6  .  @  #  .  .  #  5  4  #  .  .  #  .  6  #  .  .  #
20  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #  #

--------------------------------------------------

Total Enemies: 47
Score        : 1450

--------------------------------------------------

Hero Positions and Health:

 > B: 8, at V-4
 > E: 6, at M-15
 > H: 12, at K-7

--------------------------------------------------
```

`#` walls · `.` floor · `@` furniture · `B E H` your heroes · digits are enemies,
showing their remaining health.

## Building

```sh
make
```

Needs a C compiler and `make`. On Windows, MinGW-w64 or MSYS2 provides both.
Builds clean with `-Wall -Wextra`.

To run it:

```sh
./game          # Linux / macOS
game.exe        # Windows
```

## Playing

Pick a party of up to five heroes, choose a difficulty, and set the map size.
Each hero gets one move and one action per turn. Clear every enemy to advance;
the dungeon grows roughly 15% each level, up to 99×99.

| Hero | Health | Movement | Role |
|---|---|---|---|
| **B** Barbarian | 8 | 8 tiles | Frontline melee |
| **D** Dwarf | 7 | 6 tiles | Melee, strikes diagonally |
| **E** Elf | 6 | 12 tiles | Ranged, cannot hit adjacent targets |
| **W** Wizard | 4 | 10 tiles | Ranged, ignores obstacles |
| **H** Healer | 12 | 4 tiles | Restores allies, cannot attack |

Commands are `<hero>>` followed by the action:

```
B>R3D2     move the Barbarian 3 right, then 2 down
E>A*D5     Elf attacks the enemy at D5
H>HEAL     heal every ally within 5 tiles
M>I3       spawn or remove an enemy at I3
X          end turn
Q          quit
```

Combat is dice-based: attacks roll for damage, the defender rolls to block, and
the difference comes off their health.

## How it works

**Dungeon generation.** Each level after the first draws a set of vertical walls
at pseudo-random intervals, connects them with horizontal runs, and carves a door
into every segment so the result stays fully traversable. A hallway is then cut
through the middle to join the top and bottom halves.

**Room detection.** Once the walls are down, a flood fill labels every connected
region of floor with a room ID. The generator uses those labels to distribute
furniture and enemies per-room rather than scattering them uniformly, so rooms
feel populated and corridors stay clear.

**Enemy AI.** Enemies within 5 tiles of a hero path toward the nearest one using
breadth-first search over the grid, reconstructing the route through a parent
map and walking up to 11 tiles along it. Enemies that reach an adjacent tile
attack instead of moving.

**Layout.** `Headers/` holds the interfaces and shared constants, `Source/` the
implementations — roughly 2,000 lines split by concern: grid generation,
pathfinding, hero and enemy stats, command parsing, rendering.

## Memory safety

The project was audited with AddressSanitizer, UndefinedBehaviorSanitizer,
Valgrind, `gcc -fanalyzer` and the Clang static analyzer. That found and fixed:

- **Four reachable stack buffer overflows** in the command parsers. Each was the
  same shape — a `while (isalpha/isdigit)` loop writing into a fixed-size buffer
  with no bound on the index, where the length check ran *after* the writes. All
  four were triggerable by typing a long string at the move prompt.
- **An unbounded heap write.** The enemy array was sized from the *starting* map
  dimensions and never reallocated, while the map grew every level; neither spawn
  path checked capacity.
- **A grid ownership bug.** The per-level resize was written to local variables
  instead of the live dimensions, so the map stopped growing after level 1, every
  level leaked rows, and units could spawn outside the playable area.
- **An infinite loop on EOF.** A closed input stream spun the menu loops forever
  and left `fgets` buffers uninitialised.
- **Unchecked allocations** throughout the grid code.

To reproduce the audit:

```sh
make debug
./game
```

That builds with ASan and UBSan. It needs a toolchain that ships them — Linux,
macOS, or WSL. Most MinGW builds do not include the sanitizer runtimes, so on
Windows use WSL for this target; the normal `make` build works everywhere.

Current status: clean build at `-Wall -Wextra`, no sanitizer findings, and no
leaks across map sizes from 10×10 to 99×99.
