#ifndef FAJLKEZELES_H
#define FAJLKEZELES_H
#include <stdbool.h>
#include "tipusok.h"

bool Beolvas_megallok(char path[], Megallok **kimegallok, int *ki_db);
bool Beolvasas_jaratok(char path[], Jaratok **kijaratok, int *ki_db);
bool Beolvasas_menetrendek(char path[], Menetrendek **kimenetrendek, int *ki_db);
bool Fajlkezeles(Megallok **megallok, Jaratok **jaratok, Menetrendek **menetrendek, int *megallok_szama, int *jaratok_szama, int *menetrendek_szama);

bool Mentes_megallok(char path[],Megallok *megallok);
bool Mentes_jaratok(const char path[], Jaratok *jaratok);
bool Mentes_menetrendek(const char path[], Menetrendek *menetrendek);
bool Adatok_mentese(Megallok *megallok, Jaratok *jaratok, Menetrendek *menetrendek);

#endif