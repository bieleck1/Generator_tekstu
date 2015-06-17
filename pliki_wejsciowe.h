#ifndef PLIKI_WEJSCIOWE_H
#define PLIKI_WEJSCIOWE_H

#include <stdio.h>

typedef struct element {
        struct element * next;
        char *nazwa_pliku;
} pliki_t;


#endif
