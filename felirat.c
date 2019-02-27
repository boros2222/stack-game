#include <stdio.h>

#include "nehezseg.h"
#include "econio.h"

#include "felirat.h"

// Információkat ír ki játék közben
void info_kiir (int sz, int m, int *pont, nehezseg_opcio *neh, int *hatralevo, int *nyitas) {
    int perc = *hatralevo/60;
    int masodperc = *hatralevo%60;

    textcolor(3);
    gotoxy(sz+3,2);
    printf("Pontszam:");
    textcolor(11);
    gotoxy(sz+13,2);
    printf("   ");
    gotoxy(sz+13,2);
    printf("%d", *pont);

    textcolor(3);
    gotoxy(sz+3,3);
    printf("Hatralevo ido:");
    textcolor(11);
    gotoxy(sz+18,3);
    printf("%2d:%02d", perc, masodperc);

    textcolor(3);
    gotoxy(sz+3,4);
    printf("Hatralevo nyitasok:");
    textcolor(11);
    gotoxy(sz+23,4);
    printf("   ");
    gotoxy(sz+23,4);
    printf("%d", *nyitas);

    textcolor(3);
    gotoxy(sz+3,5);
    printf("Nehezseg:");
    textcolor(11);
    gotoxy(sz+13,5);
    if (*neh == konnyu_v)
        printf("konnyu");
    else if (*neh == kozepes_v)
        printf("kozepes");
    else if (*neh == nehez_v)
        printf("nehez");

    textcolor(8);
    gotoxy(sz+3,7);
    printf("Iranyitas:");
    textcolor(7);
    gotoxy(sz+3,8);
    printf("Mozgas: nyilakkal");
    gotoxy(sz+3,9);
    printf("Mezo nyitasa: enter");
    gotoxy(sz+3,10);
    printf("Kilepes: ESC");

    textcolor(8);
    gotoxy(sz+3,12);
    printf("Elojelvaltas szabalyai:");
    textcolor(7);
    gotoxy(sz+3,13);
    printf("%c pozitiv + negativ = pozitiv", 175);
    gotoxy(sz+3,14);
    printf("%c negativ + negativ = pozitiv", 175);
    gotoxy(sz+3,15);
    printf("%c negativ + pozitiv = negativ", 175);
    gotoxy(sz+3,16);
    printf("%c pozitiv + pozitiv = negativ", 175);

}

// A játék logóját rajzolja ki
void felirat_kiir (int x, int m) {
    textcolor(14);
    gotoxy(x,m+1);
    printf("###   #####    ##     ###   #  #   #");
    gotoxy(x,m+2);
    printf("#       #     #  #   #      # #    #");
    gotoxy(x,m+3);
    printf("###     #     ####   #      ##     #");
    gotoxy(x,m+4);
    printf("  #     #     #  #   #      # #     ");
    gotoxy(x,m+5);
    printf("###     #     #  #    ###   #  #   #");
    textcolor(7);
}
