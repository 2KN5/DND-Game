## DND-Game
##
##   make           build the game
##   make debug     build with AddressSanitizer + UBSan (see README)
##   make clean     remove the binary

CC       ?= gcc
CFLAGS   ?= -Wall -Wextra -O2
CPPFLAGS := -IHeaders
LDLIBS   := -lm

SRC := $(wildcard Source/*.c)
HDR := $(wildcard Headers/*.h)

BIN := game
ifeq ($(OS),Windows_NT)
    BIN    := game.exe
    RM_BIN := if exist $(BIN) del /Q $(BIN)
else
    RM_BIN := rm -f $(BIN)
endif

SAN_FLAGS := -Wall -Wextra -g -O1 \
             -fsanitize=address,undefined -fno-omit-frame-pointer

all: $(BIN)

$(BIN): $(SRC) $(HDR)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SRC) -o $@ $(LDLIBS)

# Rebuilt from scratch so the sanitiser flags apply to every file.
debug:
	$(MAKE) clean
	$(MAKE) $(BIN) CFLAGS="$(SAN_FLAGS)"

clean:
	$(RM_BIN)

.PHONY: all debug clean
