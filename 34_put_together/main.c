#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Could not open the file!\n");
    return NULL; 
  }

  counts_t * counts_out = createCounts(); 

  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, f) >= 0) {
    stripNewline(line);
    char * testvalue = lookupValue(kvPairs, line); 
    addCount(counts_out, testvalue); 
    free(line); 
    line = NULL; 
  }
  free(line); 
  if (fclose(f) != 0) {
    fprintf(stderr, "Could not close the file!\n"); 
  }
  return counts_out;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc == 1) {
    fprintf(stderr, "Please provide kay-value files and input files\n");
    return EXIT_FAILURE;
  }
  if (argc == 2) {
    fprintf(stderr, "Please provide at lease one inputfile!\n");
    return EXIT_FAILURE; 
  }

  kvarray_t * kv = readKVs(argv[1]); 

  for (int i = 2; i<argc; i++) {
 //count from 2 to argc (call the number you count i)

    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv); 
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w"); 
    //print the counts from c into the FILE f
    printCounts(c, f); 
    //close f
    if (fclose(f) != 0) {
      fprintf(stderr, "Could not close the count output file!\n");
      return EXIT_FAILURE;
    }
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
  freeKVs(kv);
 //free the memory for kv

  return EXIT_SUCCESS;
}
