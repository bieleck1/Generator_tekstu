#ifndef GENERACJA_H
#define GENERACJA_H

#include "baza.h"

baza_t generuj(baza_t baza, char *plik_wyjsciowy, int akapity, int slowa, int stopien);
char * nowy_prefix (char * prefix, char * sufix, int stopien);
char * pierwszy_prefix (char * prefix, baza_t baza);

#endif
