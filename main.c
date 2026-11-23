#include <stdio.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "tipusok.h"
#include "menu.h"
#include "debugmalloc.h"

int main(void)
{
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
#endif

    Megallok *megallok = NULL;
    int megallok_szama = 0;
    Jaratok *jaratok = NULL;
    int jaratok_szama = 0;
    Menetrendek *menetrendek = NULL;
    int menetrendek_szama = 0;

    Menu_futtatas(&megallok, &jaratok, &menetrendek,
                  &megallok_szama, &jaratok_szama, &menetrendek_szama);

    Minden_felszabadit(&megallok, &jaratok, &menetrendek);
    return 0;
}
