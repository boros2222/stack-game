#ifndef JATEK_H
#define JATEK_H

#include "nehezseg.h"
#include <stdbool.h>

typedef struct {
    int x,y,szam;
    bool nyitva;
} mezo;

void mezo_rajzol (mezo m);
void mezo_lepes (mezo m);
void mezo_kinyit (mezo *m, int *pont, int *elozo, int *mostani, int *nyitas);

void szamok_rajzol (mezo **tomb, int mmag, int mszel);
void szamok_feltolt (mezo **tomb, int mmag, int mszel, int mag, int szel);
void szamok_modosit (mezo **tomb, int magas, int szeles, int elozo, int mostani);
void szamok_foglal (mezo*** tomb, int magas, int szeles);

void ido (int max, time_t start, int *hatralevo);
void varj (int max);

void negyzet_rajzol(int mag, int szel, int kezdmag, int kezdszel);
bool palya_hatar(char c, int y, int x, int mmag, int mszel);
void jatek_indit (nehezseg_opcio nehezs);
void jatek_vege (int pont);

#endif // JATEK_H
