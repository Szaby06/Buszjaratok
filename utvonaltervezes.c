#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utvonaltervezes.h"
#include "jaratok_menetrendek.h"
#include "debugmalloc.h"

bool Kozvetlen_jaratok(Jaratok *jarat, char *ind, char *cel, Megallok *megallok, int *menetido)
{

    int indi = -1;
    int indido = 0;
    int celi = -1;
    int celido = 0;
    int poz = 0;
    for (JaratMegallo *jm = jarat->megallok; jm != NULL; jm = jm->kov)
    {
        char *megallo = Megallo_keres_id(megallok, jm->megallo_id);
        if (megallo == NULL)
            continue;
        if (strcmp(megallo, ind) == 0)
        {
            indi = poz;
            indido = jm->menetido;
        }
        if (strcmp(megallo, cel) == 0)
        {
            celi = poz;
            celido = jm->menetido;
        }
        poz++;
    }
    if (indi != -1 && celi != -1 && indi < celi)
    {
        *menetido = celido - indido;
        return true;
    }
    return false;
}

void Egy_atszallasos(Jaratok *jaratok, int jaratok_szama, char *ind, Megallok *megallok, char *cel, AtszallosUtvonal *atszallasok, int *atszall_db)
{
    *atszall_db = 0;

    for (Jaratok *j1 = jaratok; j1 != NULL; j1 = j1->kov)
    {
        JaratMegallo *ind_jm = NULL;
        for (JaratMegallo *jm = j1->megallok; jm != NULL; jm = jm->kov)
        {
            char *nev = Megallo_keres_id(megallok, jm->megallo_id);
            if (nev != NULL && strcmp(nev, ind) == 0)
            {
                ind_jm = jm;
                break;
            }
        }
        if (ind_jm == NULL)
            continue;

        for (JaratMegallo *jm2 = ind_jm->kov; jm2 != NULL; jm2 = jm2->kov)
        {
            const char *koztes_nev = Megallo_keres_id(megallok, jm2->megallo_id);
            if (koztes_nev == NULL)
                continue;

            int menetido_koztesig = jm2->menetido - ind_jm->menetido;

            for (Jaratok *j2 = jaratok; j2 != NULL; j2 = j2->kov)
            {
                if (j1 != j2)
                {
                    int menetido_koztestol = 0;
                    if (Kozvetlen_jaratok(j2, (char *)koztes_nev, cel, megallok, &menetido_koztestol))
                    {
                        strcpy(atszallasok[*atszall_db].jarat_id1, j1->id);
                        strcpy(atszallasok[*atszall_db].jarat_id2, j2->id);
                        strcpy(atszallasok[*atszall_db].atszallas_helye, koztes_nev);
                        atszallasok[*atszall_db].teljes_menetido = menetido_koztesig + menetido_koztestol;
                        (*atszall_db)++;
                    }
                }
            }
        }
    }
}

void Kozvetlen_max(int *kozvetlen_menetidok, int kozvetlen_db, int *max, int *maxi, int *kozvetlen)
{
    *max = kozvetlen_menetidok[*maxi];
    *kozvetlen = 1;
    for (int i = 1; i < kozvetlen_db; i++)
    {
        if (kozvetlen_menetidok[i] > kozvetlen_menetidok[*maxi])
        {
            *maxi = i;
            *max = kozvetlen_menetidok[i];
            *kozvetlen = 1;
        }
    }
}
void Kozvetlen_min(int *kozvetlen_menetidok, int kozvetlen_db, int *min, int *mini, int *kozvetlen)
{
    *min = kozvetlen_menetidok[*mini];
    *kozvetlen = 1;
    for (int i = 1; i < kozvetlen_db; i++)
    {
        if (kozvetlen_menetidok[i] < kozvetlen_menetidok[*mini])
        {
            *mini = i;
            *min = kozvetlen_menetidok[i];
            *kozvetlen = 1;
        }
    }
}

void Atszall_max(AtszallosUtvonal *atszallasok, int atszall_db, int *max, int *maxi, int *kozvetlen)
{
    for (int i = 0; i < atszall_db; i++)
    {
        if (atszallasok[i].teljes_menetido > *max)
        {
            *maxi = i;
            *max = atszallasok[i].teljes_menetido;
            *kozvetlen = 0;
        }
    }
}
void Atszall_min(AtszallosUtvonal *atszallasok, int atszall_db, int *min, int *mini, int *kozvetlen)
{
    for (int i = 0; i < atszall_db; i++)
    {
        if (atszallasok[i].teljes_menetido < *min)
        {
            *mini = i;
            *min = atszallasok[i].teljes_menetido;
            *kozvetlen = 0;
        }
    }
}

void Utvonal_tervezes(Megallok *megallok, int megallok_szama, Jaratok *jaratok, int jaratok_szama)
{
    char indulo[50];
    int ind_id = -1;
    char cel[50];
    int cel_id = -1;
    printf("Adja meg az indulo megallot: \n");
    scanf(" %49[^\n]", indulo);
    while (ind_id == -1)
    {
        Megallok *m = Megallo_keres_nev(megallok, indulo);
        if (m != NULL)
        {
            ind_id = m->id;
        }
        if (ind_id == -1)
        {
            printf("Ilyen megallo nem letezik, adjon meg ujat: \n");
            scanf(" %49[^\n]", indulo);
        }
    }
    printf("Adja meg a cel megallot: \n");
    scanf(" %49[^\n]", cel);
    while (cel_id == -1)
    {
        Megallok *m = Megallo_keres_nev(megallok, cel);
        if (m != NULL)
        {
            cel_id = m->id;
        }
        if (cel_id == -1)
        {
            printf("Ilyen megallo nem letezik, adjon meg ujat: \n");
            scanf(" %49[^\n]", cel);
        }
    }
    printf("%d %d \n", ind_id, cel_id);
    Jaratok **kozvetlen_jaratok = malloc(jaratok_szama * sizeof(Jaratok *));
    int *kozvetlen_jaratok_menetido = (int *)malloc(jaratok_szama * sizeof(int));
    int kozvetlenek_szama = 0;
    for (Jaratok *j = jaratok; j != NULL; j = j->kov)
    {
        if (Kozvetlen_jaratok(j, indulo, cel, megallok, &kozvetlen_jaratok_menetido[kozvetlenek_szama]))
        {
            kozvetlen_jaratok[kozvetlenek_szama] = j;
            kozvetlenek_szama++;
        }
    }

    int max_talalat = 100;
    AtszallosUtvonal *atszallasok = (AtszallosUtvonal *)malloc(max_talalat * sizeof(AtszallosUtvonal));
    int atszall_db = 0;
    Egy_atszallasos(jaratok, jaratok_szama, indulo, megallok, cel, atszallasok, &atszall_db);

    int max = 0;
    int maxi = 0;
    int mini = 0;
    int min = 10000;
    int kozvetlen_min = 0;
    int kozvetlen_max = 0;
    if (kozvetlenek_szama > 0 || atszall_db > 0)
    {
        if (kozvetlenek_szama > 0)
        {
            Kozvetlen_max(kozvetlen_jaratok_menetido, kozvetlenek_szama, &max, &maxi, &kozvetlen_max);
            Kozvetlen_min(kozvetlen_jaratok_menetido, kozvetlenek_szama, &min, &mini, &kozvetlen_min);
        }
        if (atszall_db > 0)
        {
            Atszall_max(atszallasok, atszall_db, &max, &maxi, &kozvetlen_max);
            Atszall_min(atszallasok, atszall_db, &min, &mini, &kozvetlen_min);
        }

        if (kozvetlen_max)
        {
            printf("A max kozvetlen es jaratszama: %s, menetido: %d perc\n", kozvetlen_jaratok[maxi]->id, max);
        }
        else
        {
            printf("A max atszallasos \n");
            printf("-------------------------- \n");
            printf("1. Felszallas: %s \n", atszallasok[maxi].jarat_id1);
            printf("Atszallas: %s \n", atszallasok[maxi].atszallas_helye);
            printf("2. Felszallas: %s \n", atszallasok[maxi].jarat_id2);
            printf("Teljes menetido: %d perc\n", atszallasok[maxi].teljes_menetido);
            printf("-------------------------- \n");
        }
        if (kozvetlen_min)
        {
            printf("A min kozvetlen es jaratszama: %s, menetido: %d perc\n", kozvetlen_jaratok[mini]->id, min);
        }
        else
        {
            printf("A min atszallasos \n");
            printf("-------------------------- \n");
            printf("1. Felszallas: %s \n", atszallasok[mini].jarat_id1);
            printf("Atszallas: %s \n", atszallasok[mini].atszallas_helye);
            printf("2. Felszallas: %s \n", atszallasok[mini].jarat_id2);
            printf("Teljes menetido: %d perc\n", atszallasok[mini].teljes_menetido);
            printf("-------------------------- \n");
        }
    }
    else
    {
        printf("Nincs utvonal a ket megallo kozott \n");
    }

    free(atszallasok);
    free(kozvetlen_jaratok);
    free(kozvetlen_jaratok_menetido);
}
