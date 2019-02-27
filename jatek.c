#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>

#include "nehezseg.h"
#include "econio.h"
#include "toplista.h"
#include "felirat.h"

#include "jatek.h"

#define jobbra 77
#define balra 75
#define le 80
#define fel 72
#define enter 13
#define esc 27

// Kirajzol egyetlen mezöt
void mezo_rajzol (mezo m) {
    int i,j;

    for (i=1;i<=3;i++)
    {
        for (j=1;j<=4;j++)
        {
            gotoxy(m.x,m.y);
            if (i==2 && j==2)
            {
                if (m.nyitva) {
                    if (m.szam<0) printf("%d", m.szam);
                    else if (m.szam>0) printf("+");
                }
                else printf("%c", 219);
            }
            else if (i==2 && j==3)
            {
                if (m.nyitva) {
                    if (m.szam>0) printf("%d", m.szam);
                }
                else printf("%c", 219);
            }
            else if (i==1 && j==1)
            {
                printf("%c",201);
            }
            else if (i==1 && j==4)
            {
                printf("%c", 187);
            }
            else if (i==3 && j==1)
            {
                printf("%c",200);
            }
            else if (i==3 && j==4)
            {
                printf("%c", 188);
            }
            else
            {
                if ( ( (i==1) || (i==3) ) && ( (j==2) || (j==3) ) )
                    printf("%c", 205);
                else if ( (i==2) && ( (j==1) || (j==4) ) )
                    printf("%c", 186);
            }

            m.x+=1;
        }
        m.x-=4;
        m.y+=1;
    }
}

// Színezéssel jelzi a mezöt, amin éppen állunk
void mezo_lepes (mezo m) {
    textcolor(10);
    mezo_rajzol(m);
    textcolor(7);
}

// Kinyit egy mezöt
void mezo_kinyit (mezo *m, int *pont, int *elozo, int *mostani, int *nyitas) {
    int pmennyi;

    pmennyi=*pont;
    pmennyi+=m->szam;

    if(pmennyi < 0)
        *pont = 0;
    else
        *pont += m->szam;

    *elozo = *mostani;
    *mostani = m->szam;
    m->nyitva = true;
    *nyitas-=1;
}

// Kirajzolja az összes mezöt
void szamok_rajzol (mezo **tomb, int mmag, int mszel) {
    int y,x;

    for (y=0; y<mmag; y++)
        for (x=0; x<mszel; x++) {
            mezo_rajzol(tomb[y][x]);
        }
}

// Feltölti a mezöket tartalmazót tömböt számokkal
void szamok_feltolt (mezo **tomb, int mmag, int mszel, int mag, int szel) {
    int y,x,r;

    srand(time(0));

    for (y=0; y<mmag; y++)
    {
        for (x=0; x<mszel; x++)
        {
            tomb[y][x].x=x*4+2;
            tomb[y][x].y=y*3+2;
            tomb[y][x].nyitva=false;

            r=(rand() % 16)+2;
            if (r>=2 && r<=9)
                tomb[y][x].szam=r*(-1);
            else if (r>=11 && r<=17)
                tomb[y][x].szam=r-9;
            else if (r==10)
                tomb[y][x].szam=9;
        }
    }
}

// Módosítja a háttérben a számokat a szabály szerint
void szamok_modosit (mezo **tomb, int magas, int szeles, int elozo, int mostani) {
    int y,x,k,hanyadik;
    bool pozitiv;

    if ((elozo>0 && mostani<0)|| (elozo<0 && mostani<0)) // Pozitív +- és -- esetén
        pozitiv = true;
    else if ((elozo>0 && mostani>0) || (elozo<0 && mostani>0)) // Negatív ++ és -+ esetén
        pozitiv = false;

    k = (abs(elozo)+abs(mostani))/2;

    for (y=0; y<magas; y++)
        for (x=0; x<szeles; x++) {
            hanyadik = y*szeles+x+1;
            if (hanyadik % k == 0 && tomb[y][x].nyitva == false) {
                if (pozitiv)
                    tomb[y][x].szam = abs(tomb[y][x].szam);
                else if (!pozitiv && tomb[y][x].szam>0)
                    tomb[y][x].szam = tomb[y][x].szam*(-1);
            }
        }
}

// Lefoglalja dinamikusan a tömböt
void szamok_foglal (mezo*** tomb, int magas, int szeles) {
    int y;

    *tomb = (mezo**) malloc(magas*sizeof(mezo*));
    (*tomb)[0] = (mezo*) malloc((szeles*magas)*sizeof(mezo));

    for (y=1; y<magas; y++)
        (*tomb)[y] = (*tomb)[0] + y*szeles;
}

// Megmondja, hogy mennyi idö van még hátra a játékból
void ido (int max, time_t start, int *hatralevo) {
    time_t ido1 = time(0), ido2;

    while(1) {
        if (kbhit()) break;

        ido2 = time(0);
        if ((ido2-ido1) == 1) {
            *hatralevo = max-(ido2-start);
            break;
        }
    }
}

// Paraméternek kapott számnyi másodpercet vár, ami gombnyomásra megszüntethetö
void varj (int max) {
    time_t start = time(0), ido1 = time(0), ido2;
    int hatralevo = max;

    while (hatralevo > 0) {
        if (kbhit()) {
            getch();
            break;
        }

        ido2 = time(0);
        if ((ido2-ido1) == 1) {
            hatralevo = max-(ido2-start);
            ido1 = time(0);
        }
    }
}

// Mezök köré kirajzol egy négyzetet
void negyzet_rajzol(int mag, int szel, int kezdmag, int kezdszel) {
    int i;

    textcolor(6);

    gotoxy(kezdszel,kezdmag);
    for (i=1;i<=szel;i++)
    {
        if (i==1) printf("%c",201);
        else if (i==szel) printf("%c", 187);
        else printf("%c", 205);
    }
    for (i=1;i<=(mag-2);i++)
    {
        gotoxy(kezdszel,kezdmag+i);
        printf("%c", 186);
        gotoxy(kezdszel+szel-1,kezdmag+i);
        printf("%c", 186);
    }
    gotoxy(kezdszel,kezdmag+mag-1);
    for (i=1;i<=szel;i++)
    {
        if (i==1) printf("%c",200);
        else if (i==szel) printf("%c", 188);
        else printf("%c", 205);
    }

    textcolor(7);
}

// Megmondja, hogy a pálya valamelyik szélén vagyunk-e
bool palya_hatar(char c, int y, int x, int mmag, int mszel) {
    if (c==jobbra && x==mszel-1)
        return true;
    else if (c==balra && x==0)
        return true;
    else if (c==le && y==mmag-1)
        return true;
    else if (c==fel && y==0)
        return true;
    else
        return false;
}

// Kezeli az egész játékot
void jatek_indit (nehezseg_opcio nehezs) {

    int mszeles;
    int mmagas;
    int max_ido;
    time_t start_ido=time(0);

    if (nehezs == konnyu_v) {
        mszeles = 8;
        mmagas = 5;
        max_ido = 60*5;
    }
    else if (nehezs == kozepes_v) {
        mszeles = 10;
        mmagas = 6;
        max_ido = 60*10;
    }
    else if (nehezs == nehez_v) {
        mszeles = 15;
        mmagas = 7;
        max_ido = 60*15;
    }

    int hatralevo_ido = max_ido;

    int szeles = mszeles*4+2;
    int magas = mmagas*3+2;
    int osszes = mszeles*mmagas;
    int pontszam = 0;
    int min_pontszam = toplista_min();
    int y = 0; //Függöleges lépés
    int x = 0; //Vízszintes lépés
    int elozo_nyitas = 0;
    int mostani_nyitas = 0;
    int nyitasok_szama = osszes*60/100;
    char merre = 0;
    mezo** szamok;

    clrscr();

    szamok_foglal(&szamok, mmagas, mszeles);
    szamok_feltolt(szamok, mmagas, mszeles, magas, szeles);

    negyzet_rajzol(magas, szeles, 1, 1);
    felirat_kiir(szeles/2-17 <= 0 ? 2 : szeles/2-17, magas);
    szamok_rajzol(szamok, mmagas, mszeles);

    mezo_lepes(szamok[y][x]);

    while(1)
    {
        info_kiir(szeles, magas, &pontszam, &nehezs, &hatralevo_ido, &nyitasok_szama);

        ido(max_ido+1, start_ido, &hatralevo_ido);

        info_kiir(szeles, magas, &pontszam, &nehezs, &hatralevo_ido, &nyitasok_szama);

        if (kbhit() && hatralevo_ido > 0 && nyitasok_szama > 0)
            merre = getch();

        if (merre == esc)
            break;

        if (hatralevo_ido <= 0 || nyitasok_szama <= 0) {
            varj(1);
            break;
        }

        if ((merre==jobbra || merre==balra || merre==le || merre==fel || merre==enter) && !palya_hatar(merre, y, x, mmagas, mszeles))
        {
            switch(merre) {
                case jobbra:
                    x+=1; break;

                case balra:
                    x-=1; break;

                case le:
                    y+=1; break;

                case fel:
                    y-=1; break;
            }
            if (merre == enter && szamok[y][x].nyitva == false) {
                mezo_kinyit(&szamok[y][x], &pontszam, &elozo_nyitas, &mostani_nyitas, &nyitasok_szama);
                szamok_rajzol(szamok, mmagas, mszeles);
                mezo_lepes(szamok[y][x]);

                if (elozo_nyitas != 0 && mostani_nyitas != 0)
                    szamok_modosit(szamok, mmagas, mszeles, elozo_nyitas, mostani_nyitas);
            }
            else if (merre != enter) {
                szamok_rajzol(szamok, mmagas, mszeles);
                mezo_lepes(szamok[y][x]);
            }

            merre = 0;
        }
    }

    free(szamok[0]);
    free(szamok);

    if (pontszam >= min_pontszam && pontszam != 0)
        toplista_hozzaad(pontszam);
    else
        jatek_vege(pontszam);
}

// Megjelenik a játék végén, ha nem írunk a toplistába
void jatek_vege (int pont) {
    clrscr();

    felirat_kiir(40,5);
    textcolor(12);
    gotoxy(50,15);
    printf("A jateknak vege!");
    textcolor(3);
    gotoxy(51,17);
    printf("Pontszamod: %d", pont);

    varj(2);
}
