#include <stdlib.h>
#include <stdio.h>

#include "stat.h"
#include "baza.h"

void drukuj_wejsciowe (baza_t baza) {
	baza_t bazka;
	bazka = baza;
	FILE *out = fopen("statystyki_na_wejsciu.txt", "w");
	int i, w;
	
	fprintf(out, "%30s%40s%27s%25s\n", "Prefix", "Sufix", "Ilosc wystapien", "Procent wystapien"); 

	for(i = 0; i < bazka.aktualny_rozmiar; i++) {
		for(w = 0; w < bazka.prefixy[i].ilosc_sufixow; w++) {
			fprintf(out, "%-50s%-20s%20d%30f%c\n", bazka.prefixy[i].prefix, bazka.prefixy[i].sufixy[w].sufix, bazka.prefixy[i].sufixy[w].ilosc_wejscia, (((float)bazka.prefixy[i].sufixy[w].ilosc_wejscia / (float)bazka.stat_wejsciowe) * 100), '%');
		}
	}
}

void drukuj_wyjsciowe (baza_t baza) {
	baza_t bazka;
        bazka = baza;
        FILE *out = fopen("statystyki_na_wyjsciu.txt", "w");
        int i, w;

        fprintf(out, "%30s%40s%27s%25s\n", "Prefix", "Sufix", "Ilosc wystapien", "Procent wystapien");

        for(i = 0; i < bazka.aktualny_rozmiar; i++) {
                for(w = 0; w < bazka.prefixy[i].ilosc_sufixow; w++) {
                        fprintf(out, "%-50s%-20s%20d%30f%c\n", bazka.prefixy[i].prefix, bazka.prefixy[i].sufixy[w].sufix, bazka.prefixy[i].sufixy[w].ilosc_wyjscia, (((float)bazka.prefixy[i].sufixy[w].ilosc_wyjscia / (float)bazka.stat_wyjsciowe) * 100), '%');
                }
        }
}

