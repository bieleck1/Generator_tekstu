#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "pliki_wejsciowe.h"
#include "baza.h"

void stworz_baze (baza_t *baza) {
	int i, w;
	baza->aktualny_rozmiar =0;
	baza->rozmiar = 10;

	baza->prefixy = malloc(baza->rozmiar * sizeof (ngram_t));
	if (baza->prefixy == NULL) {
		fprintf(stderr, "Brak wolnej pamieci!!!!!\n");
		exit(EXIT_FAILURE);
	}
	
	for(i = 0; i < baza->rozmiar; i++) {
		baza->prefixy[i].ilosc_sufixow = 0;
		if((baza->prefixy[i].prefix = malloc(128 * sizeof (char))) == NULL) {
			fprintf(stderr, "Brak wolnej pamieci!!!!!\n");
	                exit(EXIT_FAILURE);
		}
		if((baza->prefixy[i].sufixy = malloc(15 * sizeof (slowo_t))) == NULL) {
			fprintf(stderr, "Brak wolnej pamieci!!!!!\n");
	                exit(EXIT_FAILURE);
		}
		
		for(w = 0; w < 15; w++) {
			if((baza->prefixy[i].sufixy[w].sufix = malloc(128 * sizeof (char))) == NULL) {
				fprintf(stderr, "Brak wolnej pamieci!!!!!\n");
		                exit(EXIT_FAILURE);
			}
		}
	}
}

void powieksz_baze (baza_t *baza) {
	int i, w;
	baza->rozmiar *= 2;
	baza->prefixy = realloc(baza->prefixy, baza->rozmiar * sizeof (ngram_t));
	
        if (baza->prefixy == NULL) {
                fprintf(stderr, "Brak wolnej pamieci!!!!!\n");
                exit(EXIT_FAILURE);
        }

        for(i = baza->rozmiar / 2; i < baza->rozmiar; i++) {
                baza->prefixy[i].ilosc_sufixow = 0;
                if((baza->prefixy[i].prefix = malloc(128 * sizeof (char))) == NULL) {
                        fprintf(stderr, "Brak wolnej pamieci!!!!!\n");
                        exit(EXIT_FAILURE);
                }
                if((baza->prefixy[i].sufixy = malloc(15 * sizeof (slowo_t))) == NULL) {
                        fprintf(stderr, "Brak wolnej pamieci!!!!!\n");
                        exit(EXIT_FAILURE);
                }

                for(w = 0; w < 15; w++) {
                        if((baza->prefixy[i].sufixy[w].sufix = malloc(128 * sizeof (char))) == NULL) {
                                fprintf(stderr, "Brak wolnej pamieci!!!!!\n");
                                exit(EXIT_FAILURE);
                        }
                }
        }
}

baza_t wczytaj (pliki_t *pliki_wejsciowe, int stopien) {
	char znak;
	baza_t baza;
	stworz_baze(&baza);
	char *prefix = malloc(128 * sizeof(char));
	char *sufix = malloc(128 * sizeof(char));
	int n = 0;
	int dlugosc = 0;
	int dlugosc_suf = 0;
	int w, g;
	
	do {
		FILE *in = fopen(pliki_wejsciowe->nazwa_pliku, "r");
		if (in != NULL) {
			int state_nowy_pref = 1;
			int pierwsza = 1;

			while ((znak = fgetc(in)) != EOF) {
				int state_pref = 0;
                        	int state_sufix = 0;

				if (state_nowy_pref == 1) {
					state_nowy_pref = 0;
					prefix = malloc(128 * sizeof(char));
					dlugosc = 0;
					
					if (pierwsza == 1) {
                                        	prefix[dlugosc] = znak;
                                        	dlugosc++;
                                        	pierwsza = 0;
                                	}

                        		for (w = 1; w < stopien; w++) {
						if ( w > 1) {
                                			prefix[dlugosc] = ' ';
                                			dlugosc++;
						}

                                		while ((znak = fgetc(in)) != EOF && znak != ' ' && w != 0) {
							prefix[dlugosc] = znak;
							dlugosc++;

							if (znak == '.' || znak == '?' || znak == '!') {
								prefix = malloc(128 * sizeof(char));
								dlugosc = 0;
								w = 0;
							}
                                		}
                        		}

					prefix[dlugosc] = '\0';
				}

				if (znak != ' ' && znak != '.' && znak != '!' && znak != '?') {
					sufix[dlugosc_suf] = znak;
					dlugosc_suf++;
				} else {
					if (znak != ' ') {
						sufix[dlugosc_suf] = znak;
						dlugosc_suf++;
						state_nowy_pref = 1;
					}
					
					sufix[dlugosc_suf] = '\0';

					for (w = 0; w < baza.aktualny_rozmiar; w++) {
						if (strcmp(baza.prefixy[w].prefix, prefix) == 0) {
							state_pref = 1;
							if (baza.prefixy[w].ilosc_sufixow == 0 && strcmp(sufix, "") != 0) {
								baza.prefixy[w].sufixy[0].sufix = sufix;
								baza.prefixy[w].ilosc_sufixow++;
							} else {
								for (g = 0; g < baza.prefixy[w].ilosc_sufixow && strcmp(sufix, "") != 0; g++) {
									if (strcmp(baza.prefixy[w].sufixy[g].sufix, sufix) == 0) {
										g = baza.prefixy[w].ilosc_sufixow;
										state_sufix = 1;
									} else {
										state_sufix = 0;
									}
								}
								
								if (state_sufix == 0 && strcmp(sufix, "") != 0) {
									baza.prefixy[w].sufixy[baza.prefixy[w].ilosc_sufixow].sufix = sufix;
									baza.prefixy[w].ilosc_sufixow++;
								}
							}
							w = baza.aktualny_rozmiar;
						} else {
							state_pref = 0;
						}
					}

					if (state_pref == 0) {
						if (baza.aktualny_rozmiar == baza.rozmiar) {
							powieksz_baze(&baza);
						}
						baza.prefixy[baza.aktualny_rozmiar].prefix = prefix;

						if (strcmp(sufix, "") != 0) {
							baza.prefixy[baza.aktualny_rozmiar].sufixy[0].sufix = sufix;
							baza.prefixy[baza.aktualny_rozmiar].ilosc_sufixow++;
						}
						
						
						baza.aktualny_rozmiar++;
					}
					
					if (strcmp(sufix, "") != 0 && state_nowy_pref == 0) {
						char *tmp = prefix;
						int pom = dlugosc;
						dlugosc = 0;
						g = 0;
						prefix = malloc(128 * sizeof(char));
						
						if (stopien > 2) {
							while ( tmp[g] != ' ') {
								g++;
							}

							for (g++; g < pom; g++) {
								prefix[dlugosc] = tmp[g];
								dlugosc++;
							}

							prefix[dlugosc] = ' ';
							dlugosc++;

							for (w = 0; w < dlugosc_suf; w++) {
								prefix[dlugosc] = sufix[w];
								dlugosc++;
							}
							
							prefix[dlugosc] = '\0';
						} else {
							prefix = sufix;
						}
					}

					sufix = malloc(128 * sizeof(char));
					dlugosc_suf = 0;
				}
			}
		}

		fclose(in);
		pliki_wejsciowe = pliki_wejsciowe->next;
	} while(pliki_wejsciowe != NULL);

	return baza;
}


