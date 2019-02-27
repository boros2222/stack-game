#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

#include "econio.h"
#include "nehezseg.h"
#include "jatek.h"
#include "toplista.h"
#include "felirat.h"

#define jobbra 77
#define balra 75
#define le 80
#define fel 72
#define enter 13
#define esc 27

//Forrás: http://stackoverflow.com/questions/30126490/how-to-hide-console-cursor-in-c
void hidecursor(void)
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

// Fömenü opciói
typedef enum {
    indit_v,nehezseg_v,toplista_v,kilep_v,rossz_gomb1
} menu_opcio;


// Kirajzolja a fömenüt, ahol tudunk opciót választani
menu_opcio fomenu(void) {
    char c;

    clrscr();

    felirat_kiir(40,5);

    textcolor(12);
    gotoxy(51,13);
    printf("Valassz opciot:");
    textcolor(11);
    gotoxy(50,15);
    printf("1. Jatek inditasa");
    gotoxy(47,17);
    printf("2. Nehezseg beallitasa");
    gotoxy(53,19);
    printf("3. Toplista");
    gotoxy(52,23);
    printf("ESC. Kilepes");
    textcolor(7);

    c = getch();

    switch(c) {
        case '1':
            return indit_v;

        case '2':
            return nehezseg_v;

        case '3':
            return toplista_v;

        case esc:
            return kilep_v;

        default:
            return rossz_gomb1;
    }
}

// Meghívja a különbözö menüket
int main (void) {
    menu_opcio menu_valaszt;
    nehezseg_opcio nehez_valaszt, nehez;
    bool ok;

    hidecursor();

    nehez_valaszt = kozepes_v; //alapértelmezett nehézség
    menu_valaszt = fomenu();

    while (menu_valaszt != kilep_v)
    {
        if (menu_valaszt == indit_v) {
            jatek_indit(nehez_valaszt);
        }
        else if (menu_valaszt == nehezseg_v) {
            ok = false;
            while (!ok) {
                nehez = nehezseg();

                if(nehez == konnyu_v || nehez == kozepes_v || nehez == nehez_v || nehez == marad_v)
                    ok = true;
            }
            if (nehez != marad_v) nehez_valaszt = nehez;
        }
        else if (menu_valaszt == toplista_v) {
            while (!toplista_kiir());
        }

        menu_valaszt = fomenu();
    }

    return 0;
}
