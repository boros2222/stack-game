#ifndef TOPLISTA_H
#define TOPLISTA_H

typedef struct {
    char nev[11];
    int pont;
} lista;

void toplista_ment(void);
void toplista_olvas(void);
void toplista_rendez(void);
int toplista_min(void);
void toplista_hozzaad(int pont);
bool toplista_kiir(void);

#endif // TOPLISTA_H
