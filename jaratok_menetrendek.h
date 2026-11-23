#ifndef JARATOK_MENETRENDEK_H
#define JARATOK_MENETRENDEK_H
#include "tipusok.h"

char *Megallo_keres_id(Megallok *megallok, int id);
Megallok *Megallo_keres_nev(Megallok *megallok, char *nev);
void Jarat_kiirat(Jaratok *jaratok, int jaratok_szama, Megallok *megallok);
void Menetrendek_megtekintese(Menetrendek *menetrendek, int menetrendek_szama);

#endif