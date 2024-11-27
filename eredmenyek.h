#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

#ifndef EREDMENYEK_H_INCLUDED
#define EREDMENYEK_H_INCLUDED

typedef struct Eredmeny {
    char nev[10];
    int pontszam;
} Eredmeny;

void eredmenyek_beolvas(FILE* er, Eredmeny* ranglista);
void eredmenyek_megjelenit(Eredmeny* ranglista, SDL_Surface* screen);
void eredmenyek_kiir(Eredmeny* ranglista);
void eredmenyek_modosit(int pontszam, Eredmeny* ranglista, SDL_Surface* screen);

#endif
