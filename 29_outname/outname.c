#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  const char * ptr = inputName;
  int length = 0; 
  while (*ptr != '\0') {
    ptr++;
    length++;
  }

  char * outname;
  outname  = malloc( (length + 8) * sizeof(*outname));
  strcpy(outname, inputName); // copy the inputname into the out name 

  const char * append = ".counts";
  strcat(outname, append); // concat two strings together 

  return outname; 
}
