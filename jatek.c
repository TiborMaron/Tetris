#include "jatek.h"

Uint32 idozit(Uint32 ms, void* param) {

    /* Inicializálja az idõzítõt. */
    SDL_Event event;
    event.type = SDL_USEREVENT;
    SDL_PushEvent(&event);
    return ms;
}

void kirajzol(SDL_Surface* screen, int jatekter[][10], int pontszam) {

    /* A megfelelõ számok alapján kirajzolja a 2D-s mátrixot. */
    /* 1-5-ig a mozgatható elemek, 6-10-ig a már rögzített elemek színezése történik meg. */

    int i, j;
    char pont[5];
    sprintf(pont, "%d", pontszam);

    boxRGBA(screen, 0, 0, 250, 525, 0, 0, 0, 255);
    stringRGBA(screen, 5, 510, "Pontszam:", 255, 255, 255, 255);
    stringRGBA(screen, 150, 510, pont, 255, 255, 255, 255);
    lineRGBA(screen, 0, 501, 250, 501, 255, 255, 255, 255);

    for (i=0; i<20; i++) {
        for (j=0; j<10; j++) {
            switch (jatekter[i][j]) {
            case 1:
            case 6:
                boxRGBA(screen, 25*j, 25*i, 25*j+25, 25*i+25, 255, 255, 0, 255);
                break;
            case 2:
            case 7:
                boxRGBA(screen, 25*j, 25*i, 25*j+25, 25*i+25, 255, 0, 255, 255);
                break;
            case 3:
            case 8:
                boxRGBA(screen, 25*j, 25*i, 25*j+25, 25*i+25, 0, 255, 255, 255);
                break;
            case 4:
            case 9:
                boxRGBA(screen, 25*j, 25*i, 25*j+25, 25*i+25, 255, 0, 0, 255);
                break;
            case 5:
            case 10:
                boxRGBA(screen, 25*j, 25*i, 25*j+25, 25*i+25, 0, 255, 0, 255);
                break;
            }
        }
    }
    SDL_Flip(screen);
}

bool mozdithato(int jatekter[][10]) {

    /* Visszaadja, hogy van-e mozdithato elem a palyan. */
    int i, j;
    for (i=0; i<20; i++) {
        for (j=0; j<10; j++) {
            if (jatekter[i][j] != 0 && jatekter[i][j] < 6)
                return true;
        }
    }
    return false;
}

bool betelt (int jatekter[][10]) {

    /* Megvizsgálja, hogy a játéktér kezdõrésze foglalt-e már. */
    if (jatekter[0][3] > 5 ||
        jatekter[0][4] > 5 ||
        jatekter[0][5] > 5 ||
        jatekter[0][6] > 5 ||
        jatekter[1][3] > 5 ||
        jatekter[1][4] > 5 ||
        jatekter[1][3] > 5 ||
        jatekter[1][4] > 5)
        return true;
    else return false;
}

void ujelem(int jatekter[][10], Elemtipus* aktualis) {

    /* A véletlenszámgenerátor segítségével létrehozunk egy számot 1 és 5 között, amely szám jelenti az 5 féle játékelem egyikét. */
    /* A generált szám alapján létrehozásra kerül egy új elem a játéktér kezdõrészén. */
    int tipus = rand() % 5 + 1;
    switch (tipus) {
        case 1:
            jatekter[0][3] = 1;
            jatekter[0][4] = 1;
            jatekter[0][5] = 1;
            jatekter[0][6] = 1;
           aktualis->tipus = 1;
           aktualis->allapot = 1;
            return;
        case 2:
            jatekter[0][3] = 2;
            jatekter[0][4] = 2;
            jatekter[0][5] = 2;
            jatekter[1][5] = 2;
            aktualis->tipus = 2;
            aktualis->allapot = 1;
            return;
        case 3:
            jatekter[0][4] = 3;
            jatekter[0][5] = 3;
            jatekter[1][4] = 3;
            jatekter[1][5] = 3;
            aktualis->tipus = 3;
            aktualis->allapot = 1;
            return;
        case 4:
            jatekter[0][3] = 4;
            jatekter[0][4] = 4;
            jatekter[0][5] = 4;
            jatekter[1][4] = 4;
            aktualis->tipus = 4;
            aktualis->allapot = 1;
            return;
        case 5:
            jatekter[0][4] = 5;
            jatekter[0][5] = 5;
            jatekter[1][5] = 5;
            jatekter[1][6] = 5;
            aktualis->tipus = 5;
            aktualis->allapot = 1;
            return;
    }
}

void rogzit (int jatekter[][10]) {

    /* Rögzíti a mozdítható elemeket. */
    int i, j;
    for (i=0; i<20; i++) {
        for (j=0; j<10; j++) {
            if (jatekter[i][j] != 0 && jatekter[i][j] < 6)
                jatekter[i][j] += 5;
        }
    }
}

void zuhanas(int jatekter[][10]) {
    int i, j;

    /* Az elemek zuhanásáért felelõs függvény. */

    /* A jatekelem egy sort zuhan. */
    for (i=18; i>=0; i--) {
        for (j=0; j<10; j++) {
            if ((jatekter[i][j] != 0 ) && (jatekter[i][j] < 6)) {
                jatekter[i+1][j] = jatekter[i][j];
                jatekter[i][j] = 0;
            }
        }
    }

    /* Ha a legalsó sorba mozdítható elem kerül, az rögzítésre kerül. */
    for (i=0; i<10; i++) {
        if ((jatekter[19][i] != 0) && (jatekter[19][i] < 6))
            rogzit(jatekter);
    }

    /* Ha az elem mozdítható, de nincs alatta szabad hely, rögzítésre kerül. */
    for (i=0; i<19; i++) {
        for (j=0; j<10; j++) {
            if ((jatekter[i][j] != 0 ) && (jatekter[i][j] < 6) && (jatekter[i+1][j] > 5))
                rogzit(jatekter);
        }
    }
}

void balratol (int jatekter[][10]) {
    int i, j;

    /* Ha a bal oldali oszlopban van már mozdítható elem, akkor nem történik semmi. */
    for (i=0; i<20; i++) {
        if (((jatekter[i][0]) != 0) && ((jatekter[i][0]) < 6))
            return;
    }

    /* Ha valamelyik mozdítható elemtõl balra van egy nem mozdítható, akkor sem történik semmi. */
    for (i=1; i<10; i++) {
        for (j=0; j<20; j++) {
            if ((jatekter[j][i] != 0) && (jatekter[j][i] < 5) && (jatekter[j][i-1] != 0) && (jatekter[j][i-1] > 5))
            return;
        }
    }

    /* Ha a bal oszlopban nincs mozdítható elem, és a mozdítható elemtõl közvetlenül balra nincs rögzített, akkor az elem balra tolódik. */
    for (j=1; j<10; j++) {
        for (i=0; i<20; i++) {
            if ((jatekter[i][j] < 6) && (jatekter[i][j] != 0)) {
                jatekter[i][j-1] = jatekter[i][j];
                jatekter[i][j] = 0;
            }
        }
    }

    /* Ha az elem mozdítható, de nincs alatta szabad hely, rögzítésre kerül. */
    for (i=0; i<19; i++) {
        for (j=0; j<10; j++) {
            if ((jatekter[i][j] != 0 ) && (jatekter[i][j] < 6) && (jatekter[i+1][j] > 5))
                rogzit(jatekter);
        }
    }
}

void jobbratol (int jatekter[][10]) {
    int i, j;

    /* Ha a jobb oldali oszlopban van már mozdítható elem, akkor nem történik semmi. */
    for (i=0; i<20; i++) {
        if (((jatekter[i][9]) != 0) && ((jatekter[i][9]) < 6))
            return;
    }

    /* Ha valamelyik mozdítható elemtõl jobbra van egy nem mozdítható, akkor sem történik semmi. */
    for (i=8; i>=0; i--) {
        for (j=0; j<20; j++) {
            if ((jatekter[j][i] != 0) && (jatekter[j][i] < 5) && (jatekter[j][i+1] != 0) && (jatekter[j][i+1] > 5))
            return;
        }
    }

    /* Ha a jobb oszlopban nincs mozdítható elem, és a mozdítható elemtõl közvetlenül jobbra nincs rögzített, akkor az elem jobbra tolódik. */
    for (j=8; j>=0; j--) {
        for (i=0; i<20; i++) {
            if ((jatekter[i][j] < 6) && (jatekter[i][j] != 0)) {
                jatekter[i][j+1] = jatekter[i][j];
                jatekter[i][j] = 0;
            }
        }
    }

    /* Ha az elem mozdítható, de nincs alatta szabad hely, rögzítésre kerül. */
    for (i=0; i<19; i++) {
        for (j=0; j<10; j++) {
            if ((jatekter[i][j] != 0 ) && (jatekter[i][j] < 6) && (jatekter[i+1][j] > 5))
                rogzit(jatekter);
        }
    }
}

void lerak (int jatekter[][10]) {

    /* Lerakja a játékelemet a legalsó üres helyre. */
    do {
        zuhanas(jatekter);
    } while (mozdithato(jatekter));
}

void soreltunes_seged(int jatekter[][10], int sor) {

    /* Egy sorral lejjebb csúsztatja a játéktér elemeit amikor egy sor betelt. */
    int i, j;
    for (i = sor; i>=1; i--) {
        for (j=0; j<10; j++) {
            jatekter[i][j] = jatekter[i-1][j];
        }
    }
}

void soreltunes(int jatekter[][10], int* pontszam) {

    /* A függvény megvizsgálja, hogy van-e a játéktéren teli sor, és ha igen, akkor eltünteti azt, és megnöveli a pontszámot 10-el. */
    int i, j, cnt;
    for (i=19; i>=0; i--) {
        cnt = 0;
        for (j=0; j<10; j++) {
            if (jatekter[i][j] != 0) cnt++;
        }
        if (cnt == 10) {
            soreltunes_seged(jatekter, i);
            (*pontszam) += 10;
            i++;
        }
    }
}

void forgat_I(int jatekter[][10], Elemtipus* aktualis) {
    int i, j, cnt = 0;

    /*          ++++            */
    if (aktualis->allapot == 1) {
        /* Középpont megkeresése. */
        for (i=0; i<20; i++) {
            for (j=0; j<10; j++) {
                if (jatekter[i][j] == 1) cnt++;
                if (cnt == 3) {

                    /* A középpont megtalálása után következik a forgathatóság ellenõrzése. */
                    if ((i == 0) ||
                        (i == 18) ||
                        (i == 19)) return;
                    if ((jatekter[i+1][j] != 0)
                     || (jatekter[i-2][j] != 0)
                     || (jatekter[i-1][j] != 0)) return;

                    /* Ha elforgaható, akkor elforgatjuk. */
                    else {
                        jatekter[i+1][j] = 1;
                        jatekter[i-2][j] = 1;
                        jatekter[i-1][j] = 1;
                        jatekter[i][j+1] = 0;
                        jatekter[i][j-2] = 0;
                        jatekter[i][j-1] = 0;
                        aktualis->allapot = 2;
                        return;
                    }
                }
            }
        }
    }

    /*              +
                    +
                    +
                    +                   */
    if (aktualis->allapot == 2) {
        /* Középpont megkeresése. */
            for (j=0; j<10; j++) {
                for (i=0; i<20; i++) {
                    if (jatekter[i][j] == 1) cnt++;
                    if (cnt == 3) {

                        /* A középpont után következik a forgathatóság ellenõrzése. */
                        if ((j == 0) ||
                            (j == 1) ||
                            (j == 9)) return;
                        if ((jatekter[i][j+1] != 0)
                         || (jatekter[i][j-1] != 0)
                         || (jatekter[i][j-2] != 0)) return;

                        /* Ha elforgatható, akkor elforgatjuk. */
                        else {
                        jatekter[i][j+1] = 1;
                        jatekter[i][j-1] = 1;
                        jatekter[i][j-2] = 1;
                        jatekter[i+1][j] = 0;
                        jatekter[i-2][j] = 0;
                        jatekter[i-1][j] = 0;
                        aktualis->allapot = 1;
                        return;
                        }
                    }
                }
            }
    }
}

void forgat_L(int jatekter[][10], Elemtipus* aktualis) {
    int i, j, cnt;

    /*       +++
               +
                       */
    if (aktualis->allapot == 1) {

        /* Középpont megkeresése. */
        for (i=0; i<20; i++) {
            cnt = 0;
            for (j=0; j<10; j++) {
                if (jatekter[i][j] == 2) {
                    cnt++;
                    if (cnt == 3) {

                        /* A középpont után következik a forgathatóság ellenõrzése. */
                        if (i<2) return;
                        if ((jatekter[i-1][j] != 0) ||
                            (jatekter[i-2][j] != 0)) return;

                        /* Ha elforgatható, akkor elforgatjuk. */
                        else {
                            jatekter[i-1][j] = 2;
                            jatekter[i-2][j] = 2;
                            jatekter[i+1][j] = 0;
                            jatekter[i][j-2] = 0;
                            aktualis->allapot = 2;
                            return;
                        }
                    }
                }
            }
        }
    }

    /*          +
                +
               ++           */
    if (aktualis->allapot == 2) {

        /*Középpont megkeresése. */
        for (j=0; j<10; j++) {
            cnt = 0;
            for (i=0; i<20; i++) {
                if (jatekter[i][j] == 2) {
                    cnt++;
                    if (cnt == 3) {

                        /* A középpont után következik a forgathatóság ellenõrzése. */
                        if (j>7) return;
                        if ((jatekter[i][j+1] != 0) ||
                            (jatekter[i][j+2] != 0)) return;

                        /* Ha elforgatható, akkor elforgatjuk. */
                        else {
                            jatekter[i][j+1] = 2;
                            jatekter[i][j+2] = 2;
                            jatekter[i][j-1] = 0;
                            jatekter[i-2][j] = 0;
                            aktualis->allapot = 3;
                            return;
                        }
                    }
                }
            }
        }
    }

    /*          +
                +++           */
    if (aktualis->allapot == 3) {

        /* Középpont megkeresése. */
        for (i=0; i<20; i++) {
            cnt = 0;
            for (j=9; j>=0; j--) {
                if (jatekter[i][j] == 2) {
                    cnt++;
                    if (cnt == 3) {

                        /* Forgathatóság ellenõrzése. */
                        if (i>17) return;
                        if ((jatekter[i+1][j] != 0) ||
                            (jatekter[i+2][j] != 0)) return;

                        /* Elforgatjuk, ha lehet. */
                        else {
                            jatekter[i+1][j] = 2;
                            jatekter[i+2][j] = 2;
                            jatekter[i-1][j] = 0;
                            jatekter[i][j+2] = 0;
                            aktualis->allapot = 4;
                            return;
                        }
                    }
                }
            }
        }
    }

    /*          ++
                +
                +           */
    if (aktualis->allapot == 4) {

        /* Középpont megkeresése. */
        for (j=0; j<10; j++) {
            cnt = 0;
            for (i=20; i>=0; i--) {
                if (jatekter[i][j] == 2) {
                    cnt++;
                    if (cnt == 3) {

                        /* Forgathatóság ellenõrzése. */
                        if (j<2) return;
                        if ((jatekter[i][j-1] != 0) ||
                            (jatekter[i][j-2] != 0)) return;

                        /* Ha elforgatható, akkor elforgatjuk. */
                        else {
                            jatekter[i][j-1] = 2;
                            jatekter[i][j-2] = 2;
                            jatekter[i][j+1] = 0;
                            jatekter[i+2][j] = 0;
                            aktualis->allapot = 1;
                            return;
                        }
                    }
                }
            }
        }
    }
}

void forgat_T(int jatekter[][10], Elemtipus* aktualis) {
    int i, j, cnt;

    /*          +++
                 +              */
    if (aktualis->allapot == 1) {
        for (j=0; j<10; j++) {
            cnt = 0;
            for (i=19; i>=0; i--) {
                if (jatekter[i][j] == 4) {
                    cnt++;
                    if (cnt == 2) {

                        /* Forgathatóság ellenõrzése. */
                        if (i == 0) return;
                        if (jatekter[i-1][j] != 0) return;

                        /* Elforgatjuk, ha lehet. */
                        else {
                            jatekter[i-1][j] = 4;
                            jatekter[i][j+1] = 0;
                            aktualis->allapot = 2;
                            return;
                        }
                    }
                }
            }
        }
    }

    /*           +
                ++
                 +              */
    if (aktualis->allapot == 2) {
        for (i=0; i<20; i++) {
            cnt = 0;
            for (j=0; j<10; j++) {
                if (jatekter[i][j] == 4) {
                    cnt++;
                    if (cnt == 2) {

                        /* Forgathatóság ellenõrzése. */
                        if (j == 9) return;
                        if (jatekter[i][j+1] != 0) return;

                        /* Elforgatjuk, ha lehet. */
                        else {
                            jatekter[i][j+1] = 4;
                            jatekter[i+1][j] = 0;
                            aktualis->allapot = 3;
                            return;
                        }
                    }
                }
            }
        }
    }

    /*           +
                +++             */
    if (aktualis->allapot == 3) {
        for (j=0; j<10; j++) {
            cnt=0;
            for (i=0; i<20; i++) {
                if (jatekter[i][j] == 4) {
                    cnt++;
                    if (cnt == 2) {

                        /*Forgathatóság ellenõrzése. */
                        if (i == 19) return;
                        if (jatekter[i+1][j] != 0) return;

                        /*Elforgatjuk ha tudjuk. */
                        else {
                            jatekter[i+1][j] = 4;
                            jatekter[i][j-1] = 0;
                            aktualis->allapot = 4;
                            return;
                        }
                    }
                }
            }
        }
    }

    /*          +
                ++
                +               */
    if (aktualis->allapot == 4) {
            for (i=0; i<20; i++) {
                cnt = 0;
                for (j=9; j>=0; j--) {
                    if (jatekter[i][j] == 4) {
                        cnt++;
                        if (cnt == 2) {

                            /* Forgathatóság ellenõrzése. */
                            if (j == 0) return;
                            if (jatekter[i][j-1] != 0) return;

                            /* Elforgatjuk, ha tudjuk. */
                            else {
                                jatekter[i][j-1] = 4;
                                jatekter[i-1][j] = 0;
                                aktualis->allapot = 1;
                                return;
                            }
                        }
                    }
                }
            }
    }
}

void forgat_Z(int jatekter[][10], Elemtipus* aktualis) {
    int i, j, cnt;

    /*          ++
                 ++             */
    if (aktualis->allapot == 1) {

        /* A középpont megkeresése. */
        for (i=0; i<20; i++) {
            cnt = 0;
            for (j=0; j<10; j++) {
                if (jatekter[i][j] == 5) cnt++;
                if (cnt == 2) {

                    /* Forgathatóság ellenõrzése. */
                    if ((jatekter[i][j+1] != 0) ||
                        (jatekter[i+2][j] != 0)) return;

                    /* Ha elforgatható, elforgatjuk. */
                    else {
                        jatekter[i][j+1] = 5;
                        jatekter[i+2][j] = 5;
                        jatekter[i][j] = 0;
                        jatekter[i][j-1] = 0;
                        aktualis->allapot = 2;
                        return;
                    }
                }
            }
        }
    }

    /*           +
                ++
                +              */
    if (aktualis->allapot == 2) {

        /* A középpont megkeresése. */
        for (i=0; i<20; i++) {
            for (j=0; j<10; j++) {
                if (jatekter[i][j] == 5) {

                    /* Forgathatóság ellenõrzése. */
                    if (j == 9) return;
                    if ((jatekter[i+2][j] != 0) ||
                        (jatekter[i+2][j+1]) != 0) return;

                    /* Ha elforgatható, elforgatjuk. */
                    else {
                        jatekter[i+2][j] = 5;
                        jatekter[i+2][j+1] = 5;
                        jatekter[i][j] = 0;
                        jatekter[i+2][j-1] = 0;
                        aktualis->allapot = 1;
                        return;
                    }
                }
            }
        }
    }
}

void forgatas(Elemtipus* aktualis, int jatekter[][10]) {

    /* Megvizsgálja, hogy az éppen aktuális játékelem milyen típusú, és az alapján hívja meg a segédfüggvényt a forgatáshoz. */
    switch (aktualis->tipus) {
        case 1:
            forgat_I(jatekter, aktualis);
            return;
        case 2:
            forgat_L(jatekter, aktualis);
            return;
        case 3:
            return;
        case 4:
            forgat_T(jatekter, aktualis);
            return;
        case 5:
            forgat_Z(jatekter, aktualis);
            return;
    }
}

void jatekvege(int pontszam, SDL_Surface* screen) {
    char veglegespont[5];
    SDL_Event event;

    /* Játék vége felirat kirajzolása, és pontszám kiírása. */
    sprintf(veglegespont, "%d", pontszam);
    boxRGBA(screen, 0, 0, 250, 525, 0, 0, 0, 255);
    stringRGBA(screen, 60, 100, "A jateknak vege!", 255, 255, 255, 255);
    stringRGBA(screen, 60, 120, "A pontszamod: ", 255, 255, 255, 255);
    stringRGBA(screen, 200, 120, veglegespont, 255, 255, 255, 255);
    SDL_Flip(screen);

    while (SDL_WaitEvent(&event) && event.type != SDL_QUIT) {
        switch (event.type) {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_RETURN) return;
        }
    }
}

int jatek(SDL_Surface* screen) {

    /* Játéktér létrehozása. */
    SDL_TimerID id;
    SDL_Event event;
    int (*jatekter)[10] = calloc(20, sizeof(*jatekter));
    int pontszam = 0;
    Elemtipus aktualis;

    /* Az idõzítõ inicializálása. */
    id = SDL_AddTimer(1000, idozit, NULL);

    /* A legelsõ játékelem megjelenítése. */
    ujelem(jatekter, &aktualis);
    kirajzol(screen, jatekter, pontszam);

    /* A játék futása. */
    while (SDL_WaitEvent(&event) && event.type != SDL_QUIT) {

        switch (event.type) {

            /* Ha nincs felhasználói interakció, akkor az adott játékelem másodpercenként egy blokknyit zuhan. */
            case SDL_USEREVENT:
                zuhanas(jatekter);
                if (!(mozdithato(jatekter))) {
                        soreltunes(jatekter, &pontszam);
                        if (betelt(jatekter)) {
                            free(jatekter);
                            jatekter = NULL;
                            SDL_RemoveTimer(id);
                            jatekvege(pontszam, screen);
                            return pontszam;
                        }
                        ujelem(jatekter, &aktualis);
                }
                kirajzol(screen, jatekter, pontszam);

            case SDL_KEYDOWN:

                /* A bal nyílbillentyû megnyomására az adott játékelem balra tolódik egy blokknyit. */
                if (event.key.keysym.sym == SDLK_LEFT) {
                    balratol(jatekter);
                    kirajzol(screen, jatekter, pontszam);
                }

                /* A jobb nyílbillenytû megnyomására az adott játékelem jobbra tolódik egy blokknyit. */
                if (event.key.keysym.sym == SDLK_RIGHT) {
                    jobbratol(jatekter);
                    kirajzol(screen, jatekter, pontszam);
                }

                /* A le nyílbillentyû megnyomására az adott játékelem rögtön a játéktér aljára zuhan, és rögzítésre kerül. */
                if (event.key.keysym.sym == SDLK_DOWN) {
                    lerak(jatekter);
                    soreltunes(jatekter, &pontszam);
                    if (betelt(jatekter)) {
                        free(jatekter);
                        jatekter = NULL;
                        SDL_RemoveTimer(id);
                        jatekvege(pontszam, screen);
                        return pontszam;
                    }
                    ujelem(jatekter, &aktualis);
                    kirajzol(screen, jatekter, pontszam);
                }

                /* A fel nyílbillenytû megnyomására az adott játékelem megforgatásra kerül. */
                if (event.key.keysym.sym == SDLK_UP) {
                    forgatas(&aktualis, jatekter);
                    kirajzol(screen, jatekter, pontszam);
                }
        }
    }
    return -1;
}
