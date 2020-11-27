#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>




int main(int argc, char ** argv) {

    if (argc != 2) {
        fprintf(stderr, "Usage: wrong number of input parameters");
        return EXIT_FAILURE;
    }

    FILE * f = fopen(argv[1], "r");

    if (f == NULL) {
        perror("Could not open file");
        return EXIT_FAILURE;
    }

    



}