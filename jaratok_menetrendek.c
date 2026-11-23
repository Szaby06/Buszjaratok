#include <stdio.h>
#include <string.h>
#include "jaratok_menetrendek.h"
#include "debugmalloc.h"

char *Megallo_keres_id(Megallok *megallok, int id)
{
    while (megallok != NULL)
    {
        if (megallok->id == id)
        {
            return megallok->nev;
        }
        megallok = megallok->kov;
    }
    return NULL;
}

Megallok *Megallo_keres_nev(Megallok *megallok, char *nev)
{
    for (Megallok *megallo = megallok; megallo != NULL; megallo = megallo->kov)
    {
        if (strcmp(megallo->nev, nev) == 0)
        {
            return megallo;
        }
    }
    return NULL;
}

void Jarat_kiirat(Jaratok *jaratok, int jaratok_szama, Megallok *megallok)
{
    for (Jaratok *jarat = jaratok; jarat != NULL; jarat = jarat->kov)
    {
        printf("Jarat azonosito: %s\n", jarat->id);
        printf("Megallok:\n");
        for (JaratMegallo *megallo = jarat->megallok; megallo != NULL; megallo = megallo->kov)
        {
            printf("Megallo: %s, Menetido: %d perc\n", Megallo_keres_id(megallok, megallo->megallo_id), megallo->menetido);
        }
    }
}

void Menetrendek_megtekintese(Menetrendek *menetrendek, int menetrendek_szama)
{
    int ora;
    printf("Adja meg az orat (0-23): ");
    scanf("%d", &ora);
    while (ora < 0 || ora > 23)
    {
        printf("Hibas ora, adja meg ujra (0-23): ");
        scanf("%d", &ora);
    }
    printf("%d orakor ezek a jaratok kozlekednek: \n", ora);
    for (Menetrendek *menetrend = menetrendek; menetrend != NULL; menetrend = menetrend->kov)
    {
        if (menetrend->ora == ora)
        {
            printf("Jarat azonosito: %s, Gyakorisag: %d perc\n", menetrend->jarat_id, menetrend->gyak);
        }
    }
}
