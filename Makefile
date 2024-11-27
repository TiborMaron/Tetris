# Makefile a Tetris projekthez

# Compiler és kapcsolóik
CC = gcc
CFLAGS = -Wall -g `sdl-config --cflags` -I/usr/local/include/SDL -D_REENTRANT
LDFLAGS = `sdl-config --libs` -lSDL_gfx

# C forráskódok
SRCS = main.c jatek.c eredmenyek.c
OBJS = $(SRCS:.c=.o)

# Kimeneti fájl
EXEC = tetris.app

# Alapértelmezett cél: lefordítja a játékot
all: $(EXEC)

# Hogyan épüljön meg a végső bináris
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LDFLAGS)

# Fordítás szabálya
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Takarítás (törli az ideiglenes fájlokat)
clean:
	rm -f $(OBJS) $(EXEC)

# Segítség kiírása
help:
	@echo "Makefile használata:"
	@echo "  make        - A projekt lefordítása"
	@echo "  make clean  - Az objektumok és a bináris törlése"

