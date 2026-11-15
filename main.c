#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

typedef struct Megallok
{
    int id;
    char nev[50];
} Megallok;

typedef struct JaratMegallo
{
    int megallo_id, menetido;
} JaratMegallo;

typedef struct Jaratok
{
    char id[10];
    JaratMegallo *megallok;
    int megallok_szama;
} Jaratok;

typedef struct Menetrendek
{
    char jarat_id[10];
    int ora, gyak;
} Menetrendek;

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
    int noveles = 4;
    Megallok *megallok = malloc(noveles * sizeof(Megallok));

    while (fgets(sor, sizeof(sor), fp) != NULL)
    {
        // üres sorok lekezelése
        if (strlen(sor) == 0)
            continue;
        if (db >= noveles)
        {
            noveles *= 2;
            megallok = realloc(megallok, noveles * sizeof(Megallok));
        }
        Megallok megallo = {0};
        if (sscanf(sor, "%d,%49[^\n]", &megallo.id, megallo.nev) == 2)
        {
            megallok[db] = megallo;
        }
        else
        {
            printf("Hibas sor: %s", sor);
        }
        db++;
    }
    fclose(fp);
    megallok = realloc(megallok, db * sizeof(Megallok));
    *kimegallok = megallok;
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
    int noveles = 4;
    Jaratok *jaratok = malloc(noveles * sizeof(Jaratok));

    while (fgets(sor, sizeof(sor), fp) != NULL)
    {
        // üres sorok lekezelése
        if (strlen(sor) == 0)
            continue;
        if (db >= noveles)
        {
            noveles *= 2;
            jaratok = realloc(jaratok, noveles * sizeof(Jaratok));
        }
        Jaratok jarat;
        int nov_megallok = 4;
        int db_megallok = 0;
        jarat.megallok = malloc(nov_megallok * sizeof(JaratMegallo));
        char *nev = strtok(sor, ",");
        if (nev != NULL)
        {
            strncpy(jarat.id, nev, sizeof(jarat.id) - 1);
            jarat.id[sizeof(jarat.id) - 1] = '\0';
        }
        char *id = strtok(NULL, ",");
        char *ido = strtok(NULL, ",");
        while (id != NULL && ido != NULL)
        {
            if (db_megallok >= nov_megallok)
            {
                nov_megallok *= 2;
                jarat.megallok = realloc(jarat.megallok, nov_megallok * sizeof(JaratMegallo));
            }
            JaratMegallo megallo;
            megallo.megallo_id = atoi(id);
            megallo.menetido = atoi(ido);
            jarat.megallok[db_megallok] = megallo;
            db_megallok++;
            id = strtok(NULL, ",");
            ido = strtok(NULL, ",");
        }
        jarat.megallok_szama = db_megallok;
        jaratok[db] = jarat;
        db++;
    }
    fclose(fp);
    *kijaratok = jaratok;
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
    int noveles = 4;
    Menetrendek *menetrendek = malloc(noveles * sizeof(Menetrendek));

    while (fgets(sor, sizeof(sor), fp) != NULL)
    {
        // üres sorok lekezelése
        if (strlen(sor) == 0)
            continue;
        if (db >= noveles)
        {
            noveles *= 2;
            menetrendek = realloc(menetrendek, noveles * sizeof(Menetrendek));
        }
        Menetrendek menetrend = {0};
        if (sscanf(sor, "%9[^,],%d,%d[^\n]", menetrend.jarat_id, &menetrend.ora, &menetrend.gyak) == 3)
        {
            menetrendek[db] = menetrend;
        }
        else
        {
            printf("Hibas sor: %s", sor);
        }
        db++;
    }
    fclose(fp);
    menetrendek = realloc(menetrendek, db * sizeof(Menetrendek));
    *kimenetrendek = menetrendek;
    *ki_db = db;
    return true;
}

bool Fajlkezeles(Megallok **megallok, Jaratok **jaratok, Menetrendek **menetrendek, int *megallok_szama, int *jaratok_szama, int *menetrendek_szama)
{
    return Beolvasas_megallok("megallok.txt", megallok, megallok_szama) && Beolvasas_jaratok("jaratok.txt", jaratok, jaratok_szama) && Beolvasas_menetrendek("menetrendek.txt", menetrendek, menetrendek_szama);
}

void Menu_megjelenites()
{
    printf("1. Adatok betöltése: \n");
    printf("2. Járatok megtekintése\n");
    printf("3. Menetrendek megtekintése\n");
    printf("4. Útvonal tervezése\n");
    printf("5. Adatok fájlba mentése\n");
    printf("0. Kilépés\n");
}

void Jarat_kiirat(Jaratok *jaratok, int jaratok_szama, Megallok *megallok)
{
    for (int i = 0; i < jaratok_szama; i++)
    {
        printf("Járat azonosító: %s\n", jaratok[i].id);
        printf("Megállók:\n");
        for (int j = 0; j < jaratok[i].megallok_szama; j++)
        {
            printf("Megálló: %s, Menetidõ: %d perc\n", megallok[jaratok[i].megallok[j].megallo_id].nev, jaratok[i].megallok[j].menetido);
        }
    }
}

void Menetrendek_megtekintese(Menetrendek *menetrendek, int menetrendek_szama)
{
    int ora;
    printf("Adja meg az órát (0-23): ");
    scanf("%d", &ora);
    while (ora < 0 || ora > 23)
    {
        printf("Hibas ora, adja meg ujra (0-23): ");
        scanf("%d", &ora);
    }
    printf("%d órakor ezek a járatok közlekednek: \n",ora);
    for (int i = 0; i < menetrendek_szama; i++)
    {
        if (menetrendek[i].ora == ora)
        {
            printf("Járat azonosító: %s, Gyakoriság: %d perc\n", menetrendek[i].jarat_id, menetrendek[i].gyak);
        }
    }
}

//----------- ÚTVONAL TERVEZÉS ---------------------------

void Utvonal_tervezes(Megallok *megallok, int megallok_szama)
{
    char indulo[50];
    int ind_id=-1;
    char cel[50];
    int cel_id = -1;
    printf("Adja meg az indulo megallot: \n");
    scanf("%s",indulo);
    while(ind_id==-1)
    {
        for(int i=0;i<megallok_szama;i++)
        {
            if(strcmp(megallok[i].nev,indulo)==0){
                ind_id=megallok[i].id;
            }
        }
        if(ind_id==-1){
            printf("Ilyen megallo nem letezik, adjon meg ujat: \n");
            scanf("%s",indulo);
        }
    }
    printf("Adja meg a cel megallot: \n");
    scanf("%s",cel);
    while(cel_id==-1)
    {
        for(int i=0;i<megallok_szama;i++)
        {
            if(strcmp(megallok[i].nev,cel)==0){
                cel_id=megallok[i].id;
            }
        }
        if(cel_id==-1){
            printf("Ilyen megallo nem letezik, adjon meg ujat: \n");
            scanf("%s",cel);
        }
    }
    printf("%d %d",ind_id,cel_id);
}


//----------- ÚTVONAL VÉGE ---------------------------------

void Menu_futtatas(Megallok **megallok, Jaratok **jaratok, Menetrendek **menetrendek, int *megallok_szama, int *jaratok_szama, int *menetrendek_szama)
{
    int valasztas;
    do
    {
        int visszalepes = 1;
        system("cls");
        Menu_megjelenites();
        printf("Válasszon egy lehetöséget: ");
        scanf("%d", &valasztas);
        switch (valasztas)
        {
        case 1:
            system("cls");
            printf("Adatok betoltese...\n");
            if (Fajlkezeles(megallok, jaratok, menetrendek, megallok_szama, jaratok_szama, menetrendek_szama))
            {

                printf("Sikeres beolvasás! \n");
                do
                {
                    printf("Visszalépéshez nyomjon 0-át:");
                    scanf("%d", &visszalepes);
                } while (visszalepes != 0);
            }
            else
            {
                printf("Siekertelen beolvasás, a program leáll...");
                valasztas = 0;
            }
            break;
        case 2:
            system("cls");
            printf("Jaratok megtekintese:\n");
            Jarat_kiirat(*jaratok, *jaratok_szama, *megallok);
            do
            {
                printf("Visszalépéshez nyomjon 0-át:");
                scanf("%d", &visszalepes);
            } while (visszalepes != 0);
            break;
        case 3:
            system("cls");
            printf("Menetrendek megtekintese...\n");
            Menetrendek_megtekintese(*menetrendek, *menetrendek_szama);
            do
            {
                printf("Visszalépéshez nyomjon 0-át:");
                scanf("%d", &visszalepes);
            } while (visszalepes != 0);
            break;
        case 4:
            system("cls");
            printf("Utvonal tervezes...\n");
            Utvonal_tervezes(*megallok,*megallok_szama);
            do
            {
                printf("Visszalépéshez nyomjon 0-át:");
                scanf("%d", &visszalepes);
            } while (visszalepes != 0);
            break;
        case 5:
            system("cls");
            printf("Adatok fajlba mentese...\n");
            break;
        case 0:
            printf("Kilépés...\n");
            break;
        default:
            printf("Ervenytelen valasztas!\n");
            break;
        }
    } while (valasztas != 0);
}

int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    Megallok *megallok = NULL;
    int megallok_szama = 0;
    Jaratok *jaratok = NULL;
    int jaratok_szama = 0;
    Menetrendek *menetrendek = NULL;
    int menetrendek_szama = 0;
    Menu_futtatas(&megallok, &jaratok, &menetrendek, &megallok_szama, &jaratok_szama, &menetrendek_szama);

    printf("%d\n", megallok_szama);
    printf("%s\n", jaratok[1].id);
    printf("%d\n", jaratok_szama);

    free(megallok);
    free(jaratok);
    free(menetrendek);
    return 0;
}
