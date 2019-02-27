#include <stdio.h>
#include <conio.h>

#include "econio.h"
#include "felirat.h"

#include "nehezseg.h"

#define jobbra 77
#define balra 75
#define le 80
#define fel 72
#define enter 13
#define esc 27

// Kirajzolja a menüt, ahol tudunk nehézséget választani
nehezseg_opcio nehezseg(void) {
    char c;

    clrscr();

    felirat_kiir(40,5);
    textcolor(12);
    gotoxy(49,13);
    printf("Valassz nehezseget:");
    textcolor(11);
    gotoxy(54,15);
    printf("1. Konnyu");
    gotoxy(44,17);
    printf("2. Kozepes (alapertelmezett)");
    gotoxy(54,19);
    printf("3. Nehez");
    gotoxy(52,23);
    printf("ESC. Kilepes");
    textcolor(7);
    gotoxy(1,24);

    c=getch();

    switch(c) {
        case '1':
            return konnyu_v;

        case '2':
            return kozepes_v;

        case '3':
            return nehez_v;

        case esc:
            return marad_v;

        default:
            return rossz_gomb2;
    }
}
