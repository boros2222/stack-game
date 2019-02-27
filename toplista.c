#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>

#include "felirat.h"
#include "econio.h"

#include "toplista.h"

#define jobbra 77
#define balra 75
#define le 80
#define fel 72
#define enter 13
#define esc 27

lista top_tomb[10]; //Toplista tömbje globális

// Toplista tömb tartalmát kimenti fájlba
void toplista_ment(void) {
    int i;

    FILE* fp;
    fp = fopen("top.txt", "w");

    for (i=0; i<10; i++) {
        if (strcmp(top_tomb[i].nev, "#") != 0 && top_tomb[i].pont != 0)
            fprintf(fp,"%s\n%d\n",top_tomb[i].nev,top_tomb[i].pont);
    }

    fclose(fp);
}

// Fájlból beolvassa az adatokat a toplista tömbbe
void toplista_olvas(void) {
    int i;

    for (i=0;i<10;i++) {
        strcpy(top_tomb[i].nev, "#");
        top_tomb[i].pont = 0;
    }

    FILE* fp;
    fp = fopen("top.txt", "r");

    i = 0; // Toplista tömb indexének nullába állítása
    if (fp != NULL) {
        while((fscanf(fp,"%s", top_tomb[i].nev)) == 1 && i <= 10)
        {

            fscanf(fp,"%d", &top_tomb[i].pont);
            i++;
        }
    }

    fclose(fp);
}

// Rendezi a toplista tömböt pontszámok szerint csökkenö sorrendbe
void toplista_rendez(void) {
    int i,j;
    lista temp;

    for (i=0; i<10; i++)
        for (j=9; j>=i; j--)
            if (top_tomb[j].pont > top_tomb[i].pont)
            {
                temp = top_tomb[j];
                top_tomb[j] = top_tomb[i];
                top_tomb[i] = temp;
            }
}

// Megkeresi a minimum pontszámot a toplista tömbben
int toplista_min(void) {
    int i,min;

    toplista_olvas();

    min = top_tomb[0].pont;
    for (i=1; i<10; i++)
        if (top_tomb[i].pont < min)
            min = top_tomb[i].pont;

    return min;
}

// Toplistához hozzáadja az új pontszámot
void toplista_hozzaad(int pont) {
    char str[11], c;
    int i;

    clrscr();

    felirat_kiir(40,5);
    textcolor(12);
    gotoxy(50,15);
    printf("A jateknak vege!");
    textcolor(3);
    gotoxy(51,17);
    printf("Pontszamod: %d", pont);

    textcolor(7);
    gotoxy(50,19);
    printf("Add meg a neved:");
    gotoxy(49,20);
    printf("(max. 10 karakter)");
    gotoxy(53,22);
    printf("__________");
    gotoxy(53,22);

    // Név beolvasása
    str[0]='#';
    i=0;
    while (scanf("%c", &c) == 1 && i < 10)
    {
        if (c != ' ' && c != '\n') {
            str[i] = c;
            i++;
        }
        else if ((c == '\n') && str[0] == '#') {
            strcpy(str,"*Nevtelen*");
            i=10;
            break;
        }
        else if (c == '\n') {
            break;
        }
    }
    str[i]='\0';

    // Beolvasott név beírása a tömbbe
    strcpy(top_tomb[9].nev, str);
    top_tomb[9].pont = pont;

    toplista_rendez();
    toplista_ment();
}

// Kirajzolja a toplistát
bool toplista_kiir(void) {
    char c;
    int i,j,n,k;

    clrscr();

    felirat_kiir(40,5);
    textcolor(12);
    gotoxy(54,13);
    printf("Toplista:");
    textcolor(11);
    gotoxy(52,26);
    printf("ESC. Kilepes");
    textcolor(7);

    toplista_olvas();
    toplista_rendez();

    n=15; // Kezdö y koordináta
    for (i=0;i<10;i++) {
        if (i==9)
            gotoxy(49,n);
        else
            gotoxy(50,n);

        if (strcmp(top_tomb[i].nev, "#") == 0 && top_tomb[i].pont == 0)
            printf("%d. * ures *",i+1);
        else
        {
            printf("%d. ", i+1);
            printf("%s", top_tomb[i].nev);
            k = 11-strlen(top_tomb[i].nev);
            for(j=1;j<=k;j++) printf(" ");
            printf("-");
            printf(" %d", top_tomb[i].pont);

        }
        n++;
    }

    c = getch(); //Ki akarunk lépni a toplistából?

    if (c == esc)
        return true;
    else
        return false;
}
