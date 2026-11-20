#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

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
}AtszallosUtvonal;

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
        // üres sorok lekezelése
        if (strlen(sor) == 0)
            continue;

        Megallok *uj = malloc(sizeof(Megallok));
        if(uj ==NULL)
        {
            fclose(fp);
            return false;
        }
        uj->kov=NULL;
        if (sscanf(sor, "%d,%49[^\n]", &uj->id, uj->nev) == 2)
        {
            if(kezd==NULL)
            {
                kezd=uj;
                veg=uj;
            }
            else{
                veg->kov=uj;
                veg=uj;
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
    Jaratok *kezd=NULL;
    Jaratok *veg=NULL;

    while (fgets(sor, sizeof(sor), fp) != NULL)
    {
        sor[strcspn(sor,"\r\n")] ='\0';
        // üres sorok lekezelése
        if (strlen(sor) == 0)
            continue;

        Jaratok *uj = malloc(sizeof(Jaratok));
        if(uj == NULL)
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
        uj->kov=NULL;

        JaratMegallo *jm_kezd=NULL;
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
        while (id != NULL && ido!=NULL)
        {
            JaratMegallo *uj_jm= malloc(sizeof(JaratMegallo));
            if(uj_jm==NULL)
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
            uj_jm->megallo_id=atoi(id);
            uj_jm->menetido=atoi(ido);
            uj_jm->kov=NULL;

            if(jm_kezd ==NULL)
            {
                jm_kezd = uj_jm;
                jm_veg=uj_jm;
            }
            else{
                jm_veg->kov=uj_jm;
                jm_veg=uj_jm;
            }
            db_megallok++;
            id = strtok(NULL, ",");
            ido = strtok(NULL, ",");
        }
        uj->megallok= jm_kezd;
        uj->megallok_szama= db_megallok;
        if(kezd ==NULL)
        {
            kezd = uj;
            veg=uj;
        }
        else{
            veg->kov=uj;
            veg=uj;
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
    Menetrendek *kezd=NULL;
    Menetrendek *veg = NULL;

    while (fgets(sor, sizeof(sor), fp) != NULL)
    {
        sor[strcspn(sor, "\r\n")] = '\0';
        // üres sorok lekezelése
        if (strlen(sor) == 0)
            continue;

        Menetrendek *uj = malloc(sizeof(Menetrendek));
        if(uj==NULL)
        {
            fclose(fp);
            return false;
        }
        uj->kov=NULL;
        if (sscanf(sor, "%9[^,],%d,%d[^\n]", uj->jarat_id, &uj->ora, &uj->gyak) == 3)
        {
            if(kezd==NULL)
            {
                kezd = uj;
                veg=uj;
            }
            else
            {
                veg->kov=uj;
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

void Menu_megjelenites()
{
    printf("1. Adatok betöltése: \n");
    printf("2. Járatok megtekintése\n");
    printf("3. Menetrendek megtekintése\n");
    printf("4. Útvonal tervezése\n");
    printf("5. Adatok fájlba mentése\n");
    printf("0. Kilépés\n");
}

char *Megallo_keres_id(Megallok *megallok, int id)
{
    while(megallok!=NULL)
    {
        if(megallok->id==id)
        {
            return megallok->nev;
        }
        megallok = megallok->kov;
    }
    return "Ismeretlen megallo";
}

static Megallok *Megallo_keres_nev(Megallok *megallok,char *nev)
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
    for (Jaratok *jarat = jaratok; jarat!=NULL; jarat=jarat->kov)
    {
        printf("Járat azonosító: %s\n", jarat->id);
        printf("Megállók:\n");
        for (JaratMegallo *megallo=jarat->megallok;megallo!=NULL;megallo=megallo->kov)
        {
            printf("Megálló: %s, Menetidõ: %d perc\n", Megallo_keres_id(megallok,megallo->megallo_id), megallo->menetido);
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
    for (Menetrendek *menetrend = menetrendek;menetrend!=NULL;menetrend = menetrend->kov)
    {
        if (menetrend->ora == ora)
        {
            printf("Járat azonosító: %s, Gyakoriság: %d perc\n", menetrend->jarat_id, menetrend->gyak);
        }
    }
}

//----------- ÚTVONAL TERVEZÉS ---------------------------

bool Kozvetlen_jaratok(Jaratok *jarat, char *ind,char *cel,Megallok *megallok, int *menetido)
{
        int indi=-1;
        int indido=0;
        int celi=-1;
        int celido=0;
        for(int j =0;j<jarat->megallok_szama;j++)
        {
            if(strcmp(megallok[jarat->megallok[j].megallo_id].nev,ind)==0)
                {
                    indi=j;
                    indido=jarat->megallok[j].menetido;
                }
            if(strcmp(megallok[jarat->megallok[j].megallo_id].nev,cel)==0)
                {
                    celi=j;
                    celido=jarat->megallok[j].menetido;
                }
        }
        if(indi!=-1 && celi!=-1 && indi<celi)
        {
            *menetido=celido-indido;
            return true;
        }
        return false;
}

void Egy_atszallasos(Jaratok *jaratok,int jaratok_szama, char *ind,Megallok *megallok,char *cel,AtszallosUtvonal *atszallasok,int *atszall_db)
{
    *atszall_db=0;
    for(int i=0;i<jaratok_szama;i++)
        {
            int indi=-1;
            int j=0;
            while(indi==-1&&j<jaratok[i].megallok_szama)
            {
                if(strcmp(megallok[jaratok[i].megallok[j].megallo_id].nev,ind)==0)
                    {
                        indi=j;
                    }
                j++;
            }
            if(indi==-1)continue;
            for(int x =indi+1;x<jaratok[i].megallok_szama;x++)
            {
                char *koztes_nev = megallok[jaratok[i].megallok[x].megallo_id].nev;
                int menetido_koztesig=jaratok[i].megallok[x].menetido-jaratok[i].megallok[indi].menetido;
                for(int k=0;k<jaratok_szama;k++)
                {
                    if(i!=k){
                        int menetido_koztestol=0;
                        if(Kozvetlen_jaratok(&jaratok[k],koztes_nev,cel,megallok,&menetido_koztestol))
                        {
                            strcpy(atszallasok[*atszall_db].jarat_id1,jaratok[i].id);
                            strcpy(atszallasok[*atszall_db].jarat_id2,jaratok[k].id);
                            strcpy(atszallasok[*atszall_db].atszallas_helye,koztes_nev);
                            atszallasok[*atszall_db].teljes_menetido=menetido_koztesig+menetido_koztestol;
                            (*atszall_db)++;
                        }
                    }
                }

            }
        }
}


void Kozvetlen_max(int *kozvetlen_menetidok,int kozvetlen_db,int *max,int *maxi, int *kozvetlen)
{
    *max=kozvetlen_menetidok[*maxi];
    *kozvetlen =1;
    for(int i=1;i<kozvetlen_db;i++)
    {
        if(kozvetlen_menetidok[i]>kozvetlen_menetidok[*maxi])
        {
            *maxi =i;
            *max=kozvetlen_menetidok[i];
            *kozvetlen =1;
        }
    }
}
void Kozvetlen_min(int *kozvetlen_menetidok,int kozvetlen_db,int *min,int *mini,int *kozvetlen)
{
    *min=kozvetlen_menetidok[*mini];
    *kozvetlen =1;
    for(int i=1;i<kozvetlen_db;i++)
    {
        if(kozvetlen_menetidok[i]<kozvetlen_menetidok[*mini])
        {
            *mini =i;
            *min = kozvetlen_menetidok[i];
            *kozvetlen =1;
        }
    }
}

void Atszall_max(AtszallosUtvonal *atszallasok,int atszall_db,int *max,int *maxi,int *kozvetlen)
{
    for(int i=0;i<atszall_db;i++)
    {
        if(atszallasok[i].teljes_menetido>*max)
        {
            *maxi =i;
            *max = atszallasok[i].teljes_menetido;
            *kozvetlen =0;
        }
    }
}
void Atszall_min(AtszallosUtvonal *atszallasok,int atszall_db,int *min,int *mini,int *kozvetlen)
{
    for(int i=0;i<atszall_db;i++)
    {
        if(atszallasok[i].teljes_menetido<*min)
        {
            *mini =i;
            *min = atszallasok[i].teljes_menetido;
            *kozvetlen =0;
        }
    }
}



void Utvonal_tervezes(Megallok *megallok, int megallok_szama, Jaratok *jaratok, int jaratok_szama)
{
    char indulo[50];
    int ind_id=-1;
    char cel[50];
    int cel_id = -1;
    printf("Adja meg az indulo megallot: \n");
    scanf(" %49[^\n]", indulo);
    while(ind_id==-1)
    {
        Megallok *m = Megallo_keres_nev(megallok,indulo);
            if(m!=NULL){
                ind_id=m->id;
            }
        if(ind_id==-1){
            printf("Ilyen megallo nem letezik, adjon meg ujat: \n");
            scanf(" %49[^\n]", indulo);
        }
    }
    printf("Adja meg a cel megallot: \n");
    scanf(" %49[^\n]", cel);
    while(cel_id==-1)
    {
        Megallok *m = Megallo_keres_nev(megallok,indulo);
            if(m!=NULL){
                cel_id=m->id;
            }
        if(cel_id==-1){
            printf("Ilyen megallo nem letezik, adjon meg ujat: \n");
            scanf(" %49[^\n]", cel);

        }
    }
    printf("%d %d \n",ind_id,cel_id);
    int *kozvetlen_jaratok = (int*) malloc(jaratok_szama*sizeof(int));
    int *kozvetlen_jaratok_menetido = (int*) malloc(jaratok_szama*sizeof(int));
    int kozvetlenek_szama=0;
    for(int i=0;i<jaratok_szama;i++)
    {
        if(Kozvetlen_jaratok(&jaratok[i],indulo,cel,megallok, &kozvetlen_jaratok_menetido[kozvetlenek_szama])){
            kozvetlen_jaratok[kozvetlenek_szama]=i;
            kozvetlenek_szama++;
        }
    }
/*
    if(kozvetlenek_szama>0)
    {
        for(int k =0;k<kozvetlenek_szama;k++)
        {
            printf("MEGVAAGY: %s \n", jaratok[kozvetlen_jaratok[k]].id);
            printf("Menetido: %d perc \n",kozvetlen_jaratok_menetido[k]);
        }
    }
    else
        printf("Nincs közvetlen járat \n");

*/
    int max_talalat=100;
    AtszallosUtvonal *atszallasok = (AtszallosUtvonal*) malloc(max_talalat*sizeof(AtszallosUtvonal));
    int atszall_db=0;
    Egy_atszallasos(jaratok,jaratok_szama,indulo,megallok,cel,atszallasok,&atszall_db);
    /*if(atszall_db>0)
    {
        for(int i=0;i<atszall_db;i++)
        {
            printf("-------------------------- \n");
            printf("1. Felszallas: %s \n",atszallasok[i].jarat_id1);
            printf("Átszállás: %s \n",atszallasok[i].atszallas_helye);
            printf("2. Felszallas: %s \n",atszallasok[i].jarat_id2);
            printf("Teljes menetido: %d\n",atszallasok[i].teljes_menetido);
            printf("-------------------------- \n");
        }
    }*/
    int max =0;
    int maxi=0;
    int mini=0;
    int min=10000;
    int kozvetlen_min=0;
    int kozvetlen_max=0;
    if(kozvetlenek_szama>0||atszall_db>0)
    {
        if(kozvetlenek_szama>0)
        {
            Kozvetlen_max(kozvetlen_jaratok_menetido, kozvetlenek_szama,&max,&maxi,&kozvetlen_max);
            Kozvetlen_min(kozvetlen_jaratok_menetido, kozvetlenek_szama,&min,&mini,&kozvetlen_min);
        }
        if(atszall_db>0)
        {
            Atszall_max(atszallasok,atszall_db,&max,&maxi,&kozvetlen_max);
            Atszall_min(atszallasok,atszall_db,&min,&mini,&kozvetlen_min);
        }

        if(kozvetlen_max)
        {
            printf("A max kozvetlen és jaratszama: %s, menetido: %d perc\n",jaratok[kozvetlen_jaratok[maxi]].id,max);
        }
        else{
            printf("A max atszallasos \n");
            printf("-------------------------- \n");
            printf("1. Felszallas: %s \n",atszallasok[maxi].jarat_id1);
            printf("Atszallas: %s \n",atszallasok[maxi].atszallas_helye);
            printf("2. Felszallas: %s \n",atszallasok[maxi].jarat_id2);
            printf("Teljes menetido: %d perc\n",atszallasok[maxi].teljes_menetido);
            printf("-------------------------- \n");
        }
        if(kozvetlen_min)
        {
            printf("A min kozvetlen és jaratszama: %s, menetido: %d perc\n",jaratok[kozvetlen_jaratok[mini]].id,min);
        }
        else{
            printf("A min atszallasos \n");
            printf("-------------------------- \n");
            printf("1. Felszallas: %s \n",atszallasok[mini].jarat_id1);
            printf("Atszallas: %s \n",atszallasok[mini].atszallas_helye);
            printf("2. Felszallas: %s \n",atszallasok[mini].jarat_id2);
            printf("Teljes menetido: %d perc\n",atszallasok[mini].teljes_menetido);
            printf("-------------------------- \n");
        }
    }
    else{
        printf("Nincs utvonal a ket megallo kozott \n");
    }


    free(atszallasok);
    free(kozvetlen_jaratok);
    free(kozvetlen_jaratok_menetido);
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
            Utvonal_tervezes(*megallok,*megallok_szama,*jaratok,*jaratok_szama);
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
            Sleep(1500);
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
    free(megallok);
    free(jaratok);
    free(menetrendek);
    megallok=NULL;
    jaratok=NULL;
    menetrendek=NULL;
    return 0;
}
