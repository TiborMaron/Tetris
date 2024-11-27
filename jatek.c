#include "jatek.h"

Uint32 idozit(Uint32 ms, void* param) {

    /* Inicializ�lja az id�z�t�t. */
    SDL_Event event;
    event.type = SDL_USEREVENT;
    SDL_PushEvent(&event);
    return ms;
}

void kirajzol(SDL_Surface* screen, int jatekter[][10], int pontszam) {

    /* A megfelel� sz�mok alapj�n kirajzolja a 2D-s m�trixot. */
    /* 1-5-ig a mozgathat� elemek, 6-10-ig a m�r r�gz�tett elemek sz�nez�se t�rt�nik meg. */

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

    /* Megvizsg�lja, hogy a j�t�kt�r kezd�r�sze foglalt-e m�r. */
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

    /* A v�letlensz�mgener�tor seg�ts�g�vel l�trehozunk egy sz�mot 1 �s 5 k�z�tt, amely sz�m jelenti az 5 f�le j�t�kelem egyik�t. */
    /* A gener�lt sz�m alapj�n l�trehoz�sra ker�l egy �j elem a j�t�kt�r kezd�r�sz�n. */
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

    /* R�gz�ti a mozd�that� elemeket. */
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

    /* Az elemek zuhan�s��rt felel�s f�ggv�ny. */

    /* A jatekelem egy sort zuhan. */
    for (i=18; i>=0; i--) {
        for (j=0; j<10; j++) {
            if ((jatekter[i][j] != 0 ) && (jatekter[i][j] < 6)) {
                jatekter[i+1][j] = jatekter[i][j];
                jatekter[i][j] = 0;
            }
        }
    }

    /* Ha a legals� sorba mozd�that� elem ker�l, az r�gz�t�sre ker�l. */
    for (i=0; i<10; i++) {
        if ((jatekter[19][i] != 0) && (jatekter[19][i] < 6))
            rogzit(jatekter);
    }

    /* Ha az elem mozd�that�, de nincs alatta szabad hely, r�gz�t�sre ker�l. */
    for (i=0; i<19; i++) {
        for (j=0; j<10; j++) {
            if ((jatekter[i][j] != 0 ) && (jatekter[i][j] < 6) && (jatekter[i+1][j] > 5))
                rogzit(jatekter);
        }
    }
}

void balratol (int jatekter[][10]) {
    int i, j;

    /* Ha a bal oldali oszlopban van m�r mozd�that� elem, akkor nem t�rt�nik semmi. */
    for (i=0; i<20; i++) {
        if (((jatekter[i][0]) != 0) && ((jatekter[i][0]) < 6))
            return;
    }

    /* Ha valamelyik mozd�that� elemt�l balra van egy nem mozd�that�, akkor sem t�rt�nik semmi. */
    for (i=1; i<10; i++) {
        for (j=0; j<20; j++) {
            if ((jatekter[j][i] != 0) && (jatekter[j][i] < 5) && (jatekter[j][i-1] != 0) && (jatekter[j][i-1] > 5))
            return;
        }
    }

    /* Ha a bal oszlopban nincs mozd�that� elem, �s a mozd�that� elemt�l k�zvetlen�l balra nincs r�gz�tett, akkor az elem balra tol�dik. */
    for (j=1; j<10; j++) {
        for (i=0; i<20; i++) {
            if ((jatekter[i][j] < 6) && (jatekter[i][j] != 0)) {
                jatekter[i][j-1] = jatekter[i][j];
                jatekter[i][j] = 0;
            }
        }
    }

    /* Ha az elem mozd�that�, de nincs alatta szabad hely, r�gz�t�sre ker�l. */
    for (i=0; i<19; i++) {
        for (j=0; j<10; j++) {
            if ((jatekter[i][j] != 0 ) && (jatekter[i][j] < 6) && (jatekter[i+1][j] > 5))
                rogzit(jatekter);
        }
    }
}

void jobbratol (int jatekter[][10]) {
    int i, j;

    /* Ha a jobb oldali oszlopban van m�r mozd�that� elem, akkor nem t�rt�nik semmi. */
    for (i=0; i<20; i++) {
        if (((jatekter[i][9]) != 0) && ((jatekter[i][9]) < 6))
            return;
    }

    /* Ha valamelyik mozd�that� elemt�l jobbra van egy nem mozd�that�, akkor sem t�rt�nik semmi. */
    for (i=8; i>=0; i--) {
        for (j=0; j<20; j++) {
            if ((jatekter[j][i] != 0) && (jatekter[j][i] < 5) && (jatekter[j][i+1] != 0) && (jatekter[j][i+1] > 5))
            return;
        }
    }

    /* Ha a jobb oszlopban nincs mozd�that� elem, �s a mozd�that� elemt�l k�zvetlen�l jobbra nincs r�gz�tett, akkor az elem jobbra tol�dik. */
    for (j=8; j>=0; j--) {
        for (i=0; i<20; i++) {
            if ((jatekter[i][j] < 6) && (jatekter[i][j] != 0)) {
                jatekter[i][j+1] = jatekter[i][j];
                jatekter[i][j] = 0;
            }
        }
    }

    /* Ha az elem mozd�that�, de nincs alatta szabad hely, r�gz�t�sre ker�l. */
    for (i=0; i<19; i++) {
        for (j=0; j<10; j++) {
            if ((jatekter[i][j] != 0 ) && (jatekter[i][j] < 6) && (jatekter[i+1][j] > 5))
                rogzit(jatekter);
        }
    }
}

void lerak (int jatekter[][10]) {

    /* Lerakja a j�t�kelemet a legals� �res helyre. */
    do {
        zuhanas(jatekter);
    } while (mozdithato(jatekter));
}

void soreltunes_seged(int jatekter[][10], int sor) {

    /* Egy sorral lejjebb cs�sztatja a j�t�kt�r elemeit amikor egy sor betelt. */
    int i, j;
    for (i = sor; i>=1; i--) {
        for (j=0; j<10; j++) {
            jatekter[i][j] = jatekter[i-1][j];
        }
    }
}

void soreltunes(int jatekter[][10], int* pontszam) {

    /* A f�ggv�ny megvizsg�lja, hogy van-e a j�t�kt�ren teli sor, �s ha igen, akkor elt�nteti azt, �s megn�veli a pontsz�mot 10-el. */
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
        /* K�z�ppont megkeres�se. */
        for (i=0; i<20; i++) {
            for (j=0; j<10; j++) {
                if (jatekter[i][j] == 1) cnt++;
                if (cnt == 3) {

                    /* A k�z�ppont megtal�l�sa ut�n k�vetkezik a forgathat�s�g ellen�rz�se. */
                    if ((i == 0) ||
                        (i == 18) ||
                        (i == 19)) return;
                    if ((jatekter[i+1][j] != 0)
                     || (jatekter[i-2][j] != 0)
                     || (jatekter[i-1][j] != 0)) return;

                    /* Ha elforgahat�, akkor elforgatjuk. */
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
        /* K�z�ppont megkeres�se. */
            for (j=0; j<10; j++) {
                for (i=0; i<20; i++) {
                    if (jatekter[i][j] == 1) cnt++;
                    if (cnt == 3) {

                        /* A k�z�ppont ut�n k�vetkezik a forgathat�s�g ellen�rz�se. */
                        if ((j == 0) ||
                            (j == 1) ||
                            (j == 9)) return;
                        if ((jatekter[i][j+1] != 0)
                         || (jatekter[i][j-1] != 0)
                         || (jatekter[i][j-2] != 0)) return;

                        /* Ha elforgathat�, akkor elforgatjuk. */
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

        /* K�z�ppont megkeres�se. */
        for (i=0; i<20; i++) {
            cnt = 0;
            for (j=0; j<10; j++) {
                if (jatekter[i][j] == 2) {
                    cnt++;
                    if (cnt == 3) {

                        /* A k�z�ppont ut�n k�vetkezik a forgathat�s�g ellen�rz�se. */
                        if (i<2) return;
                        if ((jatekter[i-1][j] != 0) ||
                            (jatekter[i-2][j] != 0)) return;

                        /* Ha elforgathat�, akkor elforgatjuk. */
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

        /*K�z�ppont megkeres�se. */
        for (j=0; j<10; j++) {
            cnt = 0;
            for (i=0; i<20; i++) {
                if (jatekter[i][j] == 2) {
                    cnt++;
                    if (cnt == 3) {

                        /* A k�z�ppont ut�n k�vetkezik a forgathat�s�g ellen�rz�se. */
                        if (j>7) return;
                        if ((jatekter[i][j+1] != 0) ||
                            (jatekter[i][j+2] != 0)) return;

                        /* Ha elforgathat�, akkor elforgatjuk. */
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

        /* K�z�ppont megkeres�se. */
        for (i=0; i<20; i++) {
            cnt = 0;
            for (j=9; j>=0; j--) {
                if (jatekter[i][j] == 2) {
                    cnt++;
                    if (cnt == 3) {

                        /* Forgathat�s�g ellen�rz�se. */
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

        /* K�z�ppont megkeres�se. */
        for (j=0; j<10; j++) {
            cnt = 0;
            for (i=20; i>=0; i--) {
                if (jatekter[i][j] == 2) {
                    cnt++;
                    if (cnt == 3) {

                        /* Forgathat�s�g ellen�rz�se. */
                        if (j<2) return;
                        if ((jatekter[i][j-1] != 0) ||
                            (jatekter[i][j-2] != 0)) return;

                        /* Ha elforgathat�, akkor elforgatjuk. */
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

                        /* Forgathat�s�g ellen�rz�se. */
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

                        /* Forgathat�s�g ellen�rz�se. */
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

                        /*Forgathat�s�g ellen�rz�se. */
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

                            /* Forgathat�s�g ellen�rz�se. */
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

        /* A k�z�ppont megkeres�se. */
        for (i=0; i<20; i++) {
            cnt = 0;
            for (j=0; j<10; j++) {
                if (jatekter[i][j] == 5) cnt++;
                if (cnt == 2) {

                    /* Forgathat�s�g ellen�rz�se. */
                    if ((jatekter[i][j+1] != 0) ||
                        (jatekter[i+2][j] != 0)) return;

                    /* Ha elforgathat�, elforgatjuk. */
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

        /* A k�z�ppont megkeres�se. */
        for (i=0; i<20; i++) {
            for (j=0; j<10; j++) {
                if (jatekter[i][j] == 5) {

                    /* Forgathat�s�g ellen�rz�se. */
                    if (j == 9) return;
                    if ((jatekter[i+2][j] != 0) ||
                        (jatekter[i+2][j+1]) != 0) return;

                    /* Ha elforgathat�, elforgatjuk. */
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

    /* Megvizsg�lja, hogy az �ppen aktu�lis j�t�kelem milyen t�pus�, �s az alapj�n h�vja meg a seg�df�ggv�nyt a forgat�shoz. */
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

    /* J�t�k v�ge felirat kirajzol�sa, �s pontsz�m ki�r�sa. */
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

    /* J�t�kt�r l�trehoz�sa. */
    SDL_TimerID id;
    SDL_Event event;
    int (*jatekter)[10] = calloc(20, sizeof(*jatekter));
    int pontszam = 0;
    Elemtipus aktualis;

    /* Az id�z�t� inicializ�l�sa. */
    id = SDL_AddTimer(1000, idozit, NULL);

    /* A legels� j�t�kelem megjelen�t�se. */
    ujelem(jatekter, &aktualis);
    kirajzol(screen, jatekter, pontszam);

    /* A j�t�k fut�sa. */
    while (SDL_WaitEvent(&event) && event.type != SDL_QUIT) {

        switch (event.type) {

            /* Ha nincs felhaszn�l�i interakci�, akkor az adott j�t�kelem m�sodpercenk�nt egy blokknyit zuhan. */
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

                /* A bal ny�lbillenty� megnyom�s�ra az adott j�t�kelem balra tol�dik egy blokknyit. */
                if (event.key.keysym.sym == SDLK_LEFT) {
                    balratol(jatekter);
                    kirajzol(screen, jatekter, pontszam);
                }

                /* A jobb ny�lbillenyt� megnyom�s�ra az adott j�t�kelem jobbra tol�dik egy blokknyit. */
                if (event.key.keysym.sym == SDLK_RIGHT) {
                    jobbratol(jatekter);
                    kirajzol(screen, jatekter, pontszam);
                }

                /* A le ny�lbillenty� megnyom�s�ra az adott j�t�kelem r�gt�n a j�t�kt�r alj�ra zuhan, �s r�gz�t�sre ker�l. */
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

                /* A fel ny�lbillenyt� megnyom�s�ra az adott j�t�kelem megforgat�sra ker�l. */
                if (event.key.keysym.sym == SDLK_UP) {
                    forgatas(&aktualis, jatekter);
                    kirajzol(screen, jatekter, pontszam);
                }
        }
    }
    return -1;
}
