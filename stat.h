#ifndef STAT_H
#define STAT_H

#include "baza.h"

typedef struct stat {
	slowo_t *slowa;
	int ilosc;
	int aktualna_ilosc;
} stat_t;

void drukuj_wejsciowe (baza_t baza);
void drukuj_wyjsciowe (baza_t baza);

#endif
