#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fajlkezeles.h"
#include "debugmalloc.h"

bool Beolvasas_megallok(char path[], Megallok **kimegallok, int *ki_db)
{
    FILE *fp = fopen(path, "r");
    if (fp == NULL)
    {
        printf("Hiba a fajl megnyitasakor!\n");
        return false;
    }
    char sor[256];
    int db = 0;
    Megallok *kezd = NULL;
    Megallok *veg = NULL;

    while (fgets(sor, sizeof(sor), fp) != NULL)
    {
        sor[strcspn(sor, "\r\n")] = '\0';
        // ures sorok lekezelese
        if (strlen(sor) == 0)
            continue;

        Megallok *uj = malloc(sizeof(Megallok));
        if (uj == NULL)
        {
            fclose(fp);
            return false;
        }
        uj->kov = NULL;
        if (sscanf(sor, "%d,%49[^\n]", &uj->id, uj->nev) == 2)
        {
            if (kezd == NULL)
            {
                kezd = uj;
                veg = uj;
            }
            else
            {
                veg->kov = uj;
                veg = uj;
            }
            db++;
        }
        else
        {
            printf("Hibas sor: %s", sor);
            free(uj);
        }
    }
    fclose(fp);
    *kimegallok = kezd;
    *ki_db = db;
    return true;
}

bool Beolvasas_jaratok(char path[], Jaratok **kijaratok, int *ki_db)
{
    FILE *fp = fopen(path, "r");
    if (fp == NULL)
    {
        printf("Hiba a fajl megnyitasakor!\n");
        return false;
    }
    char sor[512];
    int db = 0;
    Jaratok *kezd = NULL;
    Jaratok *veg = NULL;

    while (fgets(sor, sizeof(sor), fp) != NULL)
    {
        sor[strcspn(sor, "\r\n")] = '\0';
        // ures sorok lekezelese
        if (strlen(sor) == 0)
            continue;

        Jaratok *uj = malloc(sizeof(Jaratok));
        if (uj == NULL)
        {
            if (uj == NULL)
            {
                while (kezd != NULL)
                {
                    Jaratok *j_kov = kezd->kov;
                    JaratMegallo *m_akt = kezd->megallok;
                    while (m_akt != NULL)
                    {
                        JaratMegallo *m_kov = m_akt->kov;
                        free(m_akt);
                        m_akt = m_kov;
                    }
                    free(kezd);
                    kezd = j_kov;
                }
                fclose(fp);
                return false;
            }
        }
        uj->kov = NULL;

        JaratMegallo *jm_kezd = NULL;
        JaratMegallo *jm_veg = NULL;
        int db_megallok = 0;

        char *nev = strtok(sor, ",");
        if (nev != NULL)
        {
            strncpy(uj->id, nev, sizeof(uj->id) - 1);
            uj->id[sizeof(uj->id) - 1] = '\0';
        }

        char *id = strtok(NULL, ",");
        char *ido = strtok(NULL, ",");
        while (id != NULL && ido != NULL)
        {
            JaratMegallo *uj_jm = malloc(sizeof(JaratMegallo));
            if (uj_jm == NULL)
            {
                while (jm_kezd != NULL)
                {
                    JaratMegallo *kov = jm_kezd->kov;
                    free(jm_kezd);
                    jm_kezd = kov;
                }
                free(uj);
                while (kezd != NULL)
                {
                    Jaratok *j_kov = kezd->kov;
                    JaratMegallo *m_akt = kezd->megallok;
                    while (m_akt != NULL)
                    {
                        JaratMegallo *m_kov = m_akt->kov;
                        free(m_akt);
                        m_akt = m_kov;
                    }
                    free(kezd);
                    kezd = j_kov;
                }
                fclose(fp);
                return false;
            }
            uj_jm->megallo_id = atoi(id);
            uj_jm->menetido = atoi(ido);
            uj_jm->kov = NULL;

            if (jm_kezd == NULL)
            {
                jm_kezd = uj_jm;
                jm_veg = uj_jm;
            }
            else
            {
                jm_veg->kov = uj_jm;
                jm_veg = uj_jm;
            }
            db_megallok++;
            id = strtok(NULL, ",");
            ido = strtok(NULL, ",");
        }
        uj->megallok = jm_kezd;
        uj->megallok_szama = db_megallok;
        if (kezd == NULL)
        {
            kezd = uj;
            veg = uj;
        }
        else
        {
            veg->kov = uj;
            veg = uj;
        }
        db++;
    }
    fclose(fp);
    *kijaratok = kezd;
    *ki_db = db;
    return true;
}

bool Beolvasas_menetrendek(char path[], Menetrendek **kimenetrendek, int *ki_db)
{
    FILE *fp = fopen(path, "r");
    if (fp == NULL)
    {
        printf("Hiba a fajl megnyitasakor!\n");
        return false;
    }
    char sor[64];
    int db = 0;
    Menetrendek *kezd = NULL;
    Menetrendek *veg = NULL;

    while (fgets(sor, sizeof(sor), fp) != NULL)
    {
        sor[strcspn(sor, "\r\n")] = '\0';
        // ures sorok lekezelese
        if (strlen(sor) == 0)
            continue;

        Menetrendek *uj = malloc(sizeof(Menetrendek));
        if (uj == NULL)
        {
            fclose(fp);
            return false;
        }
        uj->kov = NULL;
        if (sscanf(sor, "%9[^,],%d,%d[^\n]", uj->jarat_id, &uj->ora, &uj->gyak) == 3)
        {
            if (kezd == NULL)
            {
                kezd = uj;
                veg = uj;
            }
            else
            {
                veg->kov = uj;
                veg = uj;
            }
            db++;
        }
        else
        {
            printf("Hibas sor: %s", sor);
            free(uj);
        }
    }
    fclose(fp);
    *kimenetrendek = kezd;
    *ki_db = db;
    return true;
}

bool Fajlkezeles(Megallok **megallok, Jaratok **jaratok, Menetrendek **menetrendek, int *megallok_szama, int *jaratok_szama, int *menetrendek_szama)
{
    return Beolvasas_megallok("megallok.txt", megallok, megallok_szama) && Beolvasas_jaratok("jaratok.txt", jaratok, jaratok_szama) && Beolvasas_menetrendek("menetrendek.txt", menetrendek, menetrendek_szama);
}

bool Mentes_megallok(char path[], Megallok *megallok)
{
    FILE *fp = fopen(path, "w");
    if (fp == NULL)
    {
        printf("A fajlt nem sikerult megnyitni irashoz: %s\n", path);
        return false;
    }
    for (Megallok *m = megallok; m != NULL; m = m->kov)
    {
        if (fprintf(fp, "%d,%s\n", m->id, m->nev) < 0)
        {
            fclose(fp);
            return false;
        }
    }
    fclose(fp);
    return true;
}
bool Mentes_jaratok(const char path[], Jaratok *jaratok)
{
    FILE *fp = fopen(path, "w");
    if (fp == NULL)
    {
        printf("A fajlt nem sikerult megnyitni irashoz: %s\n", path);
        return false;
    }

    for (Jaratok *j = jaratok; j != NULL; j = j->kov)
    {
        if (fprintf(fp, "%s", j->id) < 0)
        {
            fclose(fp);
            return false;
        }

        for (JaratMegallo *jm = j->megallok; jm != NULL; jm = jm->kov)
        {
            if (fprintf(fp, ",%d,%d", jm->megallo_id, jm->menetido) < 0)
            {
                fclose(fp);
                return false;
            }
        }

        if (fprintf(fp, "\n") < 0)
        {
            fclose(fp);
            return false;
        }
    }

    fclose(fp);
    return true;
}

bool Mentes_menetrendek(const char path[], Menetrendek *menetrendek)
{
    FILE *fp = fopen(path, "w");
    if (fp == NULL)
    {
        printf("A fajlt nem sikerult megnyitni irashoz: %s\n", path);
        return false;
    }

    for (Menetrendek *p = menetrendek; p != NULL; p = p->kov)
    {
        if (fprintf(fp, "%s,%d,%d\n", p->jarat_id, p->ora, p->gyak) < 0)
        {
            fclose(fp);
            return false;
        }
    }

    fclose(fp);
    return true;
}

bool Adatok_mentese(Megallok *megallok, Jaratok *jaratok, Menetrendek *menetrendek)
{
    return Mentes_megallok("megallok.txt", megallok) &&
           Mentes_jaratok("jaratok.txt", jaratok) &&
           Mentes_menetrendek("menetrendek.txt", menetrendek);
}
