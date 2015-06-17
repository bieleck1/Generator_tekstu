#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "pliki_wejsciowe.h"
#include "baza.h"
#include "generacja.h"


char * usage = 	"Uzywanie: %s [ -t teksty [ -w tekst_wyjsciowy ] [ -a liczba_akapitow ] [ -s liczba_slow ] [ -n stopien_n-gramow ] ]	\n"
		"		Jesli wprowadziles nazwy plikow tekstowych podaj:							\n"
		"			-nazwe pliku wyjsciowego z sufiksem .txt		     					\n"
		"			-ilosc akapitow, z ktorej ma sie skladac wygenerowany tekst					\n"
		"			-ilosc slow, z ktorej ma sie skladac wygenerowany tekst      					\n"
		"			-stopien n-gramow, na podstawie ktorych bedzie tworzony tekst (n > 1)				\n";

int main (int argc, char **argv) {
	int opt;
	int i = 0;
 	int ilosc_akapitow = 0;
	int ilosc_slow = 0;
 	int stopien = 0;
 	char *tekst_wyjsciowy = NULL;
 	char *nazwa_programu = argv[0];
 	pliki_t *teksty_wejsciowe, *teksty;

	int w;
	for (w = 1; w < argc; w++) {
		if (strcmp("-w", argv[w]) == 0)
			i = w;
	}

 	if ((strcmp(argv[i], "-w") != 0 && (i == argc || argv[i++][0] == '-')) || argc < 1 | i == 0 || argv[2][0] == '-') {
		fprintf (stderr, usage, nazwa_programu);
		exit (EXIT_FAILURE);
 	}

	i = 0;
	
 	while( (opt = getopt (argc, argv, "t:w:a:s:n:") ) != -1) {
		switch(opt) {
		 	case 't':
		 	teksty_wejsciowe = malloc(sizeof (pliki_t));
		 	teksty_wejsciowe->nazwa_pliku = malloc((strlen(optarg) + 1) * sizeof (char) );
 	 	 	teksty_wejsciowe->nazwa_pliku = optarg;
		 	teksty = teksty_wejsciowe; 
 	 	 	while(argv[optind][0] != '-') {
				teksty_wejsciowe->next = malloc(sizeof (pliki_t));
                         	teksty_wejsciowe = teksty_wejsciowe->next;
                         	teksty_wejsciowe->next = NULL;

		 	 	teksty_wejsciowe->nazwa_pliku = malloc((strlen(argv[optind]) + 1) * sizeof (char) );
		 	 	teksty_wejsciowe->nazwa_pliku = argv[optind++];
			}
		 	break;

		 	case 'w':
		 	tekst_wyjsciowy = optarg;
		 	break;	

			case 'a':
			ilosc_akapitow = atoi(optarg);
		 	break;

                 	case 's':
                 	ilosc_slow = atoi(optarg);
                 	break;
		
		 	case 'n':
		 	stopien = atoi(optarg);
		 	break;

		 	default:                   
     		 	fprintf (stderr, usage, nazwa_programu);
      		 	exit (EXIT_FAILURE);

		}	
	}
	
	if (stopien < 2) {
		fprintf (stderr, usage, nazwa_programu);
                exit (EXIT_FAILURE);
	}
baza_t baza;
	baza = wczytaj(teksty, stopien);
generuj();
int r, f;
	for (r = 0; r < baza.aktualny_rozmiar; r++) {
		printf("%s :", baza.prefixy[r].prefix);
		
		for (f = 0; f < baza.prefixy[r].ilosc_sufixow; f++) {
			printf("%s", baza.prefixy[r].sufixy[f].sufix);
		}
		printf("\n");
	}

	teksty_wejsciowe = teksty;

	do {
		printf("%s\n", teksty->nazwa_pliku);
		teksty = teksty->next;
		free(teksty_wejsciowe);
		teksty_wejsciowe = teksty;
	} while (teksty != NULL);


printf("%d \n%d \n %d\n", ilosc_akapitow, ilosc_slow, stopien);  
 
	return 0;
}
