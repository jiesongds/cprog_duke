#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotate(char matrix[10][10]){
  char tem[10][10];
  for (int i=0; i<10; i++){
    for (int j=0; j<10; j++) {
      tem[i][j] = matrix[i][j];
    }
  }

  for (int i=0; i<10; i++){
    int k=9;
    for (int j=0; j<10; j++){
      matrix[i][j] = tem[k][i];
      k--;
    }
  }
}

int main(int argc, char** argv ) {
    if (argc != 2) {
        fprintf(stderr, "Usage: wrong number of input parameters");
        return EXIT_FAILURE;
    }

    FILE * f = fopen(argv[1], "r"); 

    if (f == NULL) {
        perror("Could not open file");
        return EXIT_FAILURE;
    }

    char char_line[12];
    char org_mx[10][10]; 
    int k = 0;

    while (fgets(char_line, 12, f) != NULL) {
        if (strchr(char_line, '\n') == NULL) {
            printf("Improper line\n");
            return EXIT_FAILURE;
        }
        
        for (int j=0; j<10; j++) {
            org_mx[k][j] = char_line[j];
            printf("%c", org_mx[k][j]);
            if (j == 9) {
                printf("\n");
            }
        }
        k++;
    }

    //printf("\nAfter rotation\n");

    if (fclose(f) != 0) {
        printf("cannot close the file");
        return EXIT_FAILURE;
    }

    rotate(org_mx);

    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++) {
            printf("%c", org_mx[i][j]);
            if (j == 9) {
                printf("\n");
            }
        }
    }

}