#ifndef UTVONALTERVEZES_H
#define UTVONALTERVEZES_H
#include <stdbool.h>
#include "tipusok.h"

bool Kozvetlen_jaratok(Jaratok *jarat, char *ind, char *cel, Megallok *megallok, int *menetido);
void Egy_atszallasos(Jaratok *jaratok, int jaratok_szama, char *ind, Megallok *megallok, char *cel, AtszallosUtvonal *atszallasok, int *atszall_db);
void Kozvetlen_max(int *kozvetlen_menetidok, int kozvetlen_db, int *max, int *maxi, int *kozvetlen);
void Kozvetlen_min(int *kozvetlen_menetidok, int kozvetlen_db, int *min, int *mini, int *kozvetlen);
void Atszall_max(AtszallosUtvonal *atszallasok, int atszall_db, int *max, int *maxi, int *kozvetlen);
void Atszall_min(AtszallosUtvonal *atszallasok, int atszall_db, int *min, int *mini, int *kozvetlen);
void Utvonal_tervezes(Megallok *megallok, int megallok_szama, Jaratok *jaratok, int jaratok_szama);
#endif