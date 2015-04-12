#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "pliki_wejsciowe.h"


char * usage = 	"Uzywanie: %s [ -t teksty [ -w tekst_wyjsciowy ] [ -a liczba_akapitow ] [ -s liczba_slow ] [ -n stopien_n-gramow ] ]	\n"
		"		Jesli wprowadziles nazwy plikow tekstowych podaj:							\n"
		"			-nazwe pliku wyjsciowego z sufiksem .txt		     					\n"
		"			-ilosc akapitow, z ktorej ma sie skladac wygenerowany tekst					\n"
		"			-ilosc slow, z ktorej ma sie skladac wygenerowany tekst      					\n"
		"			-stopien n-gramow, na podstawie ktorych bedzie tworzony tekst					\n";

int main (int argc, char **argv)
{
 int opt;
 int i = 0;
 int ilosc_akapitow = 0;
 int ilosc_slow = 0;
 int stopien = 0;
 char *tekst_wyjsciowy = NULL;
 char *nazwa_programu = argv[0];
 pliki *teksty_wejsciowe, *teksty;
 

 while( (opt = getopt (argc, argv, "t:w:a:s:n:") ) != -1)
	{
	 switch(opt)	
		{
		 case 't':
		 teksty_wejsciowe = malloc(sizeof (pliki));
		 teksty_wejsciowe->nazwa_pliku = malloc((strlen(optarg) + 1) * sizeof (char) );
 	 	 teksty_wejsciowe->nazwa_pliku = optarg;
		 teksty = teksty_wejsciowe; 
 	 	 while(argv[optind][0] != '-')
			{teksty_wejsciowe->next = malloc(sizeof (pliki));
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

 printf("%s\n", teksty->nazwa_pliku);
while((teksty = teksty->next) != NULL) {
  printf("%s\n", teksty->nazwa_pliku); 
 }

printf("%d \n%d \n%s \n %d\n", ilosc_akapitow, ilosc_slow, tekst_wyjsciowy, stopien);  



 
 return 0;
}
