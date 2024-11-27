#include "eredmenyek.h"

void eredmenyek_beolvas(FILE* er, Eredmeny* ranglista) {
    int i;

    /* A ranglista beolvasása az eredmenyek.txt fájlból. */
    for (i=0; i<10; i++) {
        fscanf(er, " %s %d", ranglista[i].nev, &ranglista[i].pontszam);
    }
}

void eredmenyek_megjelenit(Eredmeny* ranglista, SDL_Surface* screen) {
    int i;
    char pont[5];
    SDL_Event event;

    /* A ranglista kiírása a képernyõre. */
    boxRGBA(screen, 0, 0, 250, 525, 0, 0, 0, 255);
    stringRGBA(screen, 90, 100, "Ranglista", 255, 255, 255, 255);

    /* A nevek kiírása bal oldalra. */
    for (i=0; i<10; i++) {
        stringRGBA(screen, 30, 150 + (i * 15), ranglista[i].nev, 255, 255, 255, 255);
    }

    /* A nevek mellé jobb oldalra a pontszámok kiírása. */
    for (i=0; i<10; i++) {
        sprintf(pont, "%d", ranglista[i].pontszam);
        stringRGBA(screen, 200, 150 + (i * 15), pont, 255, 255, 255, 255);
    }
    SDL_Flip(screen);

    /* Várakozás az ENTER billentyű megnyomására. */
    while (SDL_WaitEvent(&event) && event.type != SDL_QUIT) {
        switch (event.type) {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_RETURN) return;
        }
    }
}

void eredmenyek_kiir(Eredmeny* ranglista) {
    int i;
    FILE* er = fopen("eredmenyek.txt", "wt");

    /* A ranglista kiírása fájlba. */
    for (i=0; i<10; i++) {
        fprintf(er, " %s %d", ranglista[i].nev, ranglista[i].pontszam);
    }
    fclose(er);
}

void eredmenyek_modosit(int pontszam, Eredmeny* ranglista, SDL_Surface* screen) {
    char nev[10];
    int i, j, cnt = 0;
    SDL_Event event;

    for (i=0; i<10; i++) {
        /* Ha a felhasználó pontszáma nagyobb mint a ranglistában található akármelyik pontszám, akkor annak a helyére kerül be. */
        if (pontszam >= ranglista[i].pontszam) {
            stringRGBA(screen, 40, 180, "Bekerultel a TOP 10-be!", 255, 255, 255, 255);
            stringRGBA(screen, 60, 200, "Ird be a neved!", 255, 255, 255, 255);
            SDL_Flip(screen);

            /* A ranglista minden egyes eleme eggyel lejjebb kerül. */
            for (j=9; j>i; j--) {
                strcpy(ranglista[j].nev, ranglista[j-1].nev);
                ranglista[j].pontszam = ranglista[j-1].pontszam;
            }

            nev[cnt] = '\0';
            /* A felhasználó nevének bekérése. */
            while (SDL_WaitEvent(&event) && event.type != SDL_QUIT) {
                switch (event.type) {
                    case SDL_KEYDOWN:
                        if (event.key.keysym.sym == SDLK_RETURN) {
                            strcpy(ranglista[i].nev, nev);
                            ranglista[i].pontszam = pontszam;
                            eredmenyek_kiir(ranglista);
                            eredmenyek_megjelenit(ranglista, screen);
                            return;
                        }
                        if (event.key.keysym.sym == SDLK_BACKSPACE) {
                            if (cnt != 0) {
                                cnt--;
                                nev[cnt] = '\0';
                                boxRGBA(screen, 50, 220, 200, 260, 0, 0, 0, 255);
                                stringRGBA(screen, 85, 240, nev, 255, 255, 255, 255);
                                SDL_Flip(screen);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_q) {
                            if (cnt != 9) {
                                nev[cnt++] = 'Q';
                                nev[cnt] = '\0';
                                stringRGBA(screen, 85, 240, nev, 255, 255, 255, 255);
                                SDL_Flip(screen);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_w) {
                            if (cnt != 9) {
                                nev[cnt++] = 'W';
                                nev[cnt] = '\0';
                                stringRGBA(screen, 85, 240, nev, 255, 255, 255, 255);
                                SDL_Flip(screen);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_e) {
                            if (cnt != 9) {
                                nev[cnt++] = 'E';
                                nev[cnt] = '\0';
                                stringRGBA(screen, 85, 240, nev, 255, 255, 255, 255);
                                SDL_Flip(screen);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_r) {
                            if (cnt != 9) {
                                nev[cnt++] = 'R';
                                nev[cnt] = '\0';
                                stringRGBA(screen, 85, 240, nev, 255, 255, 255, 255);
                                SDL_Flip(screen);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_t) {
                            if (cnt != 9) {
                                nev[cnt++] = 'T';
                                nev[cnt] = '\0';
                                stringRGBA(screen, 85, 240, nev, 255, 255, 255, 255);
                                SDL_Flip(screen);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_z) {
                            if (cnt != 9) {
                                nev[cnt++] = 'Z';
                                nev[cnt] = '\0';
                                stringRGBA(screen, 85, 240, nev, 255, 255, 255, 255);
                                SDL_Flip(screen);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_u) {
                            if (cnt != 9) {
                                nev[cnt++] = 'U';
                                nev[cnt] = '\0';
                                stringRGBA(screen, 85, 240, nev, 255, 255, 255, 255);
                                SDL_Flip(screen);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_i) {
                            if (cnt != 9) {
                                nev[cnt++] = 'I';
                                nev[cnt] = '\0';
                                stringRGBA(screen, 85, 240, nev, 255, 255, 255, 255);
                                SDL_Flip(screen);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_o) {
                            if (cnt != 9) {
                                nev[cnt++] = 'O';
                                nev[cnt] = '\0';
                                stringRGBA(screen, 85, 240, nev, 255, 255, 255, 255);
                                SDL_Flip(screen);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_p) {
                            if (cnt != 9) {
                                nev[cnt++] = 'P';
                                nev[cnt] = '\0';
                                stringRGBA(screen, 85, 240, nev, 255, 255, 255, 255);
                                SDL_Flip(screen);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_a) {
                            if (cnt != 9) {
                                nev[cnt++] = 'A';
                                nev[cnt] = '\0';
                                stringRGBA(screen, 85, 240, nev, 255, 255, 255, 255);
                                SDL_Flip(screen);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_s) {
                            if (cnt != 9) {
                                nev[cnt++] = 'S';
                                nev[cnt] = '\0';
                                stringRGBA(screen, 85, 240, nev, 255, 255, 255, 255);
                                SDL_Flip(screen);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_d) {
                            if (cnt != 9) {
                                nev[cnt++] = 'D';
                                nev[cnt] = '\0';
                                stringRGBA(screen, 85, 240, nev, 255, 255, 255, 255);
                                SDL_Flip(screen);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_f) {
                            if (cnt != 9) {
                                nev[cnt++] = 'F';
                                nev[cnt] = '\0';
                                stringRGBA(screen, 85, 240, nev, 255, 255, 255, 255);
                                SDL_Flip(screen);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_g) {
                            if (cnt != 9) {
                                nev[cnt++] = 'G';
                                nev[cnt] = '\0';
                                stringRGBA(screen, 85, 240, nev, 255, 255, 255, 255);
                                SDL_Flip(screen);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_h) {
                            if (cnt != 9) {
                                nev[cnt++] = 'H';
                                nev[cnt] = '\0';
                                stringRGBA(screen, 85, 240, nev, 255, 255, 255, 255);
                                SDL_Flip(screen);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_j) {
                            if (cnt != 9) {
                                nev[cnt++] = 'J';
                                nev[cnt] = '\0';
                                stringRGBA(screen, 85, 240, nev, 255, 255, 255, 255);
                                SDL_Flip(screen);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_k) {
                            if (cnt != 9) {
                                nev[cnt++] = 'K';
                                nev[cnt] = '\0';
                                stringRGBA(screen, 85, 240, nev, 255, 255, 255, 255);
                                SDL_Flip(screen);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_l) {
                            if (cnt != 9) {
                                nev[cnt++] = 'L';
                                nev[cnt] = '\0';
                                stringRGBA(screen, 85, 240, nev, 255, 255, 255, 255);
                                SDL_Flip(screen);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_y) {
                            if (cnt != 9) {
                                nev[cnt++] = 'Y';
                                nev[cnt] = '\0';
                                stringRGBA(screen, 85, 240, nev, 255, 255, 255, 255);
                                SDL_Flip(screen);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_x) {
                            if (cnt != 9) {
                                nev[cnt++] = 'X';
                                nev[cnt] = '\0';
                                stringRGBA(screen, 85, 240, nev, 255, 255, 255, 255);
                                SDL_Flip(screen);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_c) {
                            if (cnt != 9) {
                                nev[cnt++] = 'C';
                                nev[cnt] = '\0';
                                stringRGBA(screen, 85, 240, nev, 255, 255, 255, 255);
                                SDL_Flip(screen);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_v) {
                            if (cnt != 9) {
                                nev[cnt++] = 'V';
                                nev[cnt] = '\0';
                                stringRGBA(screen, 85, 240, nev, 255, 255, 255, 255);
                                SDL_Flip(screen);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_b) {
                            if (cnt != 9) {
                                nev[cnt++] = 'B';
                                nev[cnt] = '\0';
                                stringRGBA(screen, 85, 240, nev, 255, 255, 255, 255);
                                SDL_Flip(screen);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_n) {
                            if (cnt != 9) {
                                nev[cnt++] = 'N';
                                nev[cnt] = '\0';
                                stringRGBA(screen, 85, 240, nev, 255, 255, 255, 255);
                                SDL_Flip(screen);
                            }
                        }
                        if (event.key.keysym.sym == SDLK_m) {
                            if (cnt != 9) {
                                nev[cnt++] = 'M';
                                nev[cnt] = '\0';
                                stringRGBA(screen, 85, 240, nev, 255, 255, 255, 255);
                                SDL_Flip(screen);
                            }
                        }
                }
            }
        }
    }
}
