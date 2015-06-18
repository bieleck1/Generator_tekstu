#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *strdup (const char *s) {
    char *d = malloc (strlen (s) + 1);   // Space for length plus nul
    if (d == NULL) return NULL;          // No memory
    strcpy (d,s);                        // Copy the characters
    return d;                            // Return the new string
}

int main (int argc, char *argv[]) {


char *cos = malloc(5 * sizeof (char));
cos = "takie";

printf("%s \n", strdup(cos));

cos = strdup(cos);

printf("%s \n", cos);


return 0;
}
