#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

//define a function reading data from stdin 
char** reading_from_input(char** linep, size_t* sz, size_t* i) {
  char** lines = NULL;
  while (getline(linep, sz, stdin) >= 0) {
    lines = realloc(lines, (*i + 1) * sizeof(*lines)); 
    lines[*i] = *linep;
    *i = *i + 1;
    *linep = NULL;
  }
  free(*linep);
  return lines;
}

//define a function reading data from an input file
char** reading_from_files(char** linep, size_t* sz, size_t* i, FILE* f) {
  char** lines = NULL;
  while (getline(linep, sz, f) >= 0) {
    lines = realloc(lines, (*i + 1) * sizeof(*lines)); 
    lines[*i] = *linep;
    *i = *i + 1;
    *linep = NULL;
  }
  free(*linep);

  return lines;
}

//define a function to print the sorted data and free allocated memory 
void printData(char** lines, size_t count) {
  for (size_t i = 0; i<count; i++) {
    printf("%s", lines[i]);
    free(lines[i]);
  }
  free(lines);
}

int main(int argc, char ** argv) {
  
  //WRITE YOUR CODE HERE!
  char* line = NULL;
  size_t sz = 0; 
  size_t i = 0; 

  if (argc==1) {
    char** lines = reading_from_input(&line, &sz, &i);
    sortData(lines, i); 
    printData(lines, i); 
  }
  else {
    for (int k = 1; k<argc; k++) {
      FILE* f = fopen(argv[k], "r"); 
      if (f == NULL) {
        fprintf(stderr, "could not open the file\n");
        return EXIT_FAILURE;
      }

      char** lines = reading_from_files(&line, &sz, &i, f);

      sortData(lines, i); 
      printData(lines, i); 

      if (fclose(f) != 0) {
        fprintf(stderr, "Could not close the file\n"); 
        return EXIT_FAILURE;
      }
      line = NULL;
      sz = 0; 
      i = 0;
    }
  }
  return EXIT_SUCCESS;
}
