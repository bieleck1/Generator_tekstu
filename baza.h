#ifndef BAZA_H
#define BAZA_H

#include "pliki_wejsciowe.h"

typedef struct slowo {
        char *sufix;
	int ilosc_wejscia;
	int ilosc_wyjscia;
} slowo_t;

typedef struct ngram {
        char *prefix;
        slowo_t *sufixy;
        int ilosc_sufixow;
} ngram_t;

typedef struct baza {
	int rozmiar;
	int aktualny_rozmiar;
	ngram_t *prefixy;
	int stat_wejsciowe;
	int stat_wyjsciowe;
} baza_t;

baza_t wczytaj(pliki_t *pliki_wejsciowe, int stopien);
void stworz_baze(baza_t *baza);
void powieksz_baze(baza_t *baza);

#endif
