#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>

#ifndef JATEK_H_INCLUDED
#define JATEK_H_INCLUDED

typedef struct Elemtipus {
    int tipus, allapot;
} Elemtipus;

Uint32 idozit(Uint32 ms, void* param);
void kirajzol(SDL_Surface* screen, int jatekter[][10], int pontszam);
bool mozdithato(int jatekter[][10]);
bool betelt (int jatekter[][10]);
void ujelem(int jatekter[][10], Elemtipus* aktualis);
void rogzit (int jatekter[][10]);
void zuhanas(int jatekter[][10]);
void balratol (int jatekter[][10]);
void jobbratol (int jatekter[][10]);
void lerak (int jatekter[][10]);
void soreltunes_seged(int jatekter[][10], int sor);
void soreltunes(int jatekter[][10], int* pontszam);
void forgat_I(int jatekter[][10], Elemtipus* aktualis);
void forgat_L(int jatekter[][10], Elemtipus* aktualis);
void forgat_T(int jatekter[][10], Elemtipus* aktualis);
void forgat_Z(int jatekter[][10], Elemtipus* aktualis);
void forgatas(Elemtipus* aktualis, int jatekter[][10]);
void jatekvege(int pontszam, SDL_Surface* screen);
int jatek(SDL_Surface* screen);

#endif
