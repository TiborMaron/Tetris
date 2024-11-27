#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include "jatek.h"
#include "eredmenyek.h"

void menu(int menupont, SDL_Surface* screen) {

    /* A kiválasztott menüpont alapján újrarajzolja a menüt. */
    if (menupont == 1) {
        boxRGBA(screen, 0, 0, 250, 525, 0, 0, 0, 255);
        stringRGBA(screen, 100, 150, "TETRIS", 255, 255, 255, 255);
        stringRGBA(screen, 90, 200, "Uj jatek", 255, 0, 0, 255);
        stringRGBA(screen, 90, 220, "Eredmenyek", 255, 255, 255, 255);
        stringRGBA(screen, 90, 240, "Kilepes", 255, 255, 255, 255);
    }
    if (menupont == 2) {
        boxRGBA(screen, 0, 0, 250, 525, 0, 0, 0, 255);
        stringRGBA(screen, 100, 150, "TETRIS", 255, 255, 255, 255);
        stringRGBA(screen, 90, 200, "Uj jatek", 255, 255, 255, 255);
        stringRGBA(screen, 90, 220, "Eredmenyek", 255, 0, 0, 255);
        stringRGBA(screen, 90, 240, "Kilepes", 255, 255, 255, 255);
    }
    if (menupont == 3) {
        boxRGBA(screen, 0, 0, 250, 525, 0, 0, 0, 255);
        stringRGBA(screen, 100, 150, "TETRIS", 255, 255, 255, 255);
        stringRGBA(screen, 90, 200, "Uj jatek", 255, 255, 255, 255);
        stringRGBA(screen, 90, 220, "Eredmenyek", 255, 255, 255, 255);
        stringRGBA(screen, 90, 240, "Kilepes", 255, 0, 0, 255);
    }
    SDL_Flip(screen);
}

int main(int argc, char *argv[]) {
    SDL_Event event;
    SDL_Surface* screen;
    FILE* er = fopen("eredmenyek.txt", "rt+");
    int menupont = 1;
    int pontszam;
    Eredmeny ranglista[10] = {{"",0}};

    srand(time(0));

    /* Eredmények beolvasása fájlból. */
    if (er == NULL) perror("Nem sikerult megnyitni a fajlt!");
    eredmenyek_beolvas(er, ranglista);

    /* SDL inicializálása és ablak megnyitása. */
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    screen = SDL_SetVideoMode(250, 525, 0, SDL_ANYFORMAT);
    if (!screen) {
        fprintf(stderr, "Nem sikerult megnyitni az ablakot!\n");
        exit(1);
    }
    SDL_WM_SetCaption("TETRIS", "TETRIS");

    /* A menürendszer. */
    menu(menupont, screen);
    while (SDL_WaitEvent(&event) && event.type != SDL_QUIT) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_DOWN) {
                        if (menupont != 3) {
                            ++menupont;
                            menu(menupont, screen);
                        }
                    }
                    if (event.key.keysym.sym == SDLK_UP) {
                        if (menupont != 1) {
                            --menupont;
                            menu(menupont, screen);
                        }
                    }
                    if (event.key.keysym.sym == SDLK_RETURN) {
                        if (menupont == 1) {
                            pontszam = jatek(screen);
                            eredmenyek_modosit(pontszam, ranglista, screen);
                            menu(menupont, screen);
                        }
                        if (menupont == 2)  {
                            eredmenyek_megjelenit(ranglista, screen);
                            menu(menupont, screen);
                        }
                        if (menupont == 3) {
                                fclose(er);
                                return 1;
                        }
                    }
            }
    }
    return 0;
}
