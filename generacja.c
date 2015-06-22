#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "baza.h"
#include "generacja.h"

char *nowy_prefix (char *prefix, char *sufix, int stopien) {
	char *tmp = prefix;
	int g = 0;
	int w;
	int dlugosc = 0;
        prefix = malloc(128 * sizeof(char));

        if (stopien > 2) {
		while (tmp[g] != ' ' && tmp[g] != '\0') {
                	g++;
                }

       		for (g++; tmp[g] != '\0'; g++) {
               		prefix[dlugosc] = tmp[g];
              		dlugosc++;
                }

                prefix[dlugosc] = ' ';
               	dlugosc++;

               	for (w = 0; sufix[w] != '\0'; w++) {
                     	prefix[dlugosc] = sufix[w];
                       	dlugosc++;
             	}

		prefix[dlugosc] = '\0';
  	} else {
		prefix = sufix;
	}

        return prefix;
}

char *pierwszy_prefix (char * prefix, baza_t baza) {
        int los = rand() % baza.aktualny_rozmiar;

        prefix = baza.prefixy[los].prefix;

        return prefix;
}


baza_t generuj (baza_t baza, char *plik_wyjsciowy,  int akapity, int slowa, int stopien) {
	int i, w, g;
	baza_t bazka;
	bazka = baza;
	char *prefix = malloc(128 * sizeof(char));
	FILE *out = fopen(plik_wyjsciowy, "w");
	int kropka = 0;

	for (i = 0; i < akapity; i++) {
		fprintf(out, "\t");		

		for (w = 0; w < (slowa / akapity + 10); w++) {
			if (w == 0 || kropka == 1) {
				prefix = pierwszy_prefix(prefix, bazka);
				if (prefix[0] > 96 && prefix[0] < 123) {
					char *tmp = malloc(128 * sizeof(char)); 
					strcpy(tmp, prefix);
					tmp[0] = tmp[0] - 32;
					fprintf(out, "%s ", tmp);
				} else {
					fprintf(out, "%s ", prefix);
				}

				kropka = 0;
				w = w + stopien - 1;
			} else {
				for(g = 0; g < bazka.aktualny_rozmiar; g++) {
					if (strcmp(prefix, bazka.prefixy[g].prefix) == 0) {
						int los = rand() % bazka.prefixy[g].ilosc_sufixow;
						fprintf(out, "%s", bazka.prefixy[g].sufixy[los].sufix);
						bazka.prefixy[g].sufixy[los].ilosc_wyjscia++;
						bazka.stat_wyjsciowe++;
						prefix = nowy_prefix(prefix, bazka.prefixy[g].sufixy[los].sufix, stopien);
						kropka = 0;
						g = bazka.aktualny_rozmiar;
					} else {
						kropka = 1;
					}				
				}
			}

			if (kropka == 1) {
				if (w > slowa / akapity ) {
					w = slowa / akapity + 10;
				} else {
					w--;
				}
			} else {
				if ((w + 1) != (slowa / akapity + 10)) {
					fprintf(out, " ");
				}
			}
		}
		
		if (kropka == 0) {
			fprintf(out, ".");
		}

		fprintf(out, "\n");
	}
	
	close(out);
	return bazka;
}
