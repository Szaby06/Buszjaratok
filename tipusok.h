#ifndef TIPUSOK_H
#define TIPUSOK_H
#include <stdbool.h>

typedef struct Megallok
{
    int id;
    char nev[50];
    struct Megallok *kov;
} Megallok;

typedef struct JaratMegallo
{
    int megallo_id, menetido;
    struct JaratMegallo *kov;
} JaratMegallo;

typedef struct Jaratok
{
    char id[10];
    JaratMegallo *megallok;
    int megallok_szama;
    struct Jaratok *kov;
} Jaratok;

typedef struct Menetrendek
{
    char jarat_id[10];
    int ora, gyak;
    struct Menetrendek *kov;
} Menetrendek;

typedef struct AtszallosUtvonal
{
    char jarat_id1[10];
    char jarat_id2[10];
    char atszallas_helye[50];
    int teljes_menetido;
} AtszallosUtvonal;

void Megallok_felszabadit(Megallok **megallok);
void Jaratok_felszabadit(Jaratok **jaratok);
void Menetrendek_felszabadit(Menetrendek **menetrendek);
void Minden_felszabadit(Megallok **megallok, Jaratok **jaratok, Menetrendek **menetrendek);
#endif