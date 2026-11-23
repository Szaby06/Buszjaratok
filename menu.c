#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "menu.h"
#include "fajlkezeles.h"
#include "jaratok_menetrendek.h"
#include "utvonaltervezes.h"
#include "tipusok.h"
#include "debugmalloc.h"

static void Kepernyo_torles(void)
{
// Elöfeldolgozó csak akkor kerül be ha Win-en fut.
#ifdef _WIN32
    system("cls");
#else
    // ANSI törlés \033=ESC, [2J =törlés, \033[H = kurzor bal fentre.
    printf("\033[2J\033[H");
#endif
}

static void Puffer_urites(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        // Puffer ürítése
    }
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

void Menu_futtatas(Megallok **megallok, Jaratok **jaratok, Menetrendek **menetrendek, int *megallok_szama, int *jaratok_szama, int *menetrendek_szama)
{
    int valasztas;
    do
    {
        int visszalepes = 1;
        Kepernyo_torles();
        Menu_megjelenites();
        printf("Valasszon egy lehetoseget: ");
        if (scanf("%d", &valasztas) != 1)
        {
            Puffer_urites();
            valasztas = -1;
        }
        switch (valasztas)
        {
        case 1:
            Kepernyo_torles();
            printf("Adatok betoltese...\n");
            Minden_felszabadit(megallok,jaratok,menetrendek);
            if (Fajlkezeles(megallok, jaratok, menetrendek, megallok_szama, jaratok_szama, menetrendek_szama))
            {

                printf("Sikeres beolvasas! \n");
                do
                {
                    printf("Visszalepeshez nyomjon 0-at:");
                    scanf("%d", &visszalepes);
                } while (visszalepes != 0);
            }
            else
            {
                printf("Siekertelen beolvasas, a program leall...");
                valasztas = 0;
            }
            break;
        case 2:
            Kepernyo_torles();
            printf("Jaratok megtekintese:\n");
            Jarat_kiirat(*jaratok, *jaratok_szama, *megallok);
            do
            {
                printf("Visszalepeshez nyomjon 0-at:");
                scanf("%d", &visszalepes);
            } while (visszalepes != 0);
            break;
        case 3:
            Kepernyo_torles();
            printf("Menetrendek megtekintese...\n");
            Menetrendek_megtekintese(*menetrendek, *menetrendek_szama);
            do
            {
                printf("Visszalepeshez nyomjon 0-at:");
                scanf("%d", &visszalepes);
            } while (visszalepes != 0);
            break;
        case 4:
            Kepernyo_torles();
            printf("Utvonal tervezes...\n");
            Utvonal_tervezes(*megallok, *megallok_szama, *jaratok, *jaratok_szama);
            do
            {
                printf("Visszalepeshez nyomjon 0-at:");
                scanf("%d", &visszalepes);
            } while (visszalepes != 0);
            break;
        case 5:
            Kepernyo_torles();
            printf("Adatok fajlba mentese...\n");
            if (Adatok_mentese(*megallok, *jaratok, *menetrendek))
            {
                printf("Sikeres mentes! \n");
            }
            else
            {
                printf("Sikertelen mentes! \n");
            }
            do
            {
                printf("Visszalepeshez nyomjon 0-at:");
                scanf("%d", &visszalepes);
            } while (visszalepes != 0);
            break;
        case 0:
            printf("Kilepes...\n");
            break;
        default:
            printf("Ervenytelen valasztas!\n");
            break;
        }
    } while (valasztas != 0);
}
