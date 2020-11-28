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

    char letters[26] = "abcdefghijklmnopqrstuvwxyz"; 

    int freq_count[26] = {0}; 

    int c; 

    int counter = 0;
    
    while ((c = fgetc(f)) != EOF && counter <=529000)
    {
      if (!isalpha(c)){
	continue;
      }
      for (int i = 0; i<26; i++) {
            if (letters[i] == c) {
                freq_count[i]++;
                break; 
            }
        }
      counter++;
    }
    
    fclose(f); 


    //for (int i =0; i<26; i++) {
        //printf("%d\n", freq_count[i]);
    //}

    int max_count = freq_count[0];
    
    for (int j = 1; j<26; j++) {
        if (freq_count[j] > max_count) {
            max_count = freq_count[j]; 
        }
    }
    int max_index; 
    for (int i = 0; i<26; i++) {
        if (freq_count[i] == max_count) {
            max_index = i;
            break;
        }
    }

    //printf("Max count is %d\n", max_count); 
    //printf("Max index is %d\n", max_index); 

    int key = (max_index + 22) % 26; 

    printf("%d\n", key); 

    return EXIT_SUCCESS; 

}
