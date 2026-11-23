#include <stdlib.h>
#include "tipusok.h"
#include "debugmalloc.h"

void Megallok_felszabadit(Megallok **megallok)
{
    Megallok *akt = *megallok;
    while (akt != NULL)
    {
        Megallok *kov = akt->kov;
        free(akt);
        akt = kov;
    }
}

void Jaratok_felszabadit(Jaratok **jaratok)
{
    Jaratok *akt = *jaratok;
    while (akt != NULL)
    {
        Jaratok *kov = akt->kov;
        JaratMegallo *jm = akt->megallok;
        while (jm != NULL)
        {
            JaratMegallo *jm_kov = jm->kov;
            free(jm);
            jm = jm_kov;
        }
        free(akt);
        akt = kov;
    }
    *jaratok = NULL;
}

void Menetrendek_felszabadit(Menetrendek **menetrendek)
{
    Menetrendek *akt = *menetrendek;
    while (akt != NULL)
    {
        Menetrendek *kov = akt->kov;
        free(akt);
        akt = kov;
    }
}

void Minden_felszabadit(Megallok **megallok, Jaratok **jaratok, Menetrendek **menetrendek)
{
    Megallok_felszabadit(megallok);
    Jaratok_felszabadit(jaratok);
    Menetrendek_felszabadit(menetrendek);
}
