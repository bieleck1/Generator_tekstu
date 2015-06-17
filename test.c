#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[]) {


int *cos = malloc(5 * sizeof (int));
cos[0] = 1;
cos[1] = 2;

free(cos);


return 0;
}
