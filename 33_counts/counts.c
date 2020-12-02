#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  //WRITE ME
  counts_t* ctarray; 
  ctarray = malloc(sizeof(*ctarray)); 
  ctarray->ct = NULL;
  ctarray->length = 0;
  ctarray->unknown_ct = 0;
  return ctarray; 
}

ssize_t find_name_idx(counts_t * c, const char * name) {
  if (c->ct == NULL) {
    return -1; 
  }
  else {
    for (size_t i=0; i<c->length; i++) {
      char * checkname = c->ct[i]->value; 
      if (strcmp(checkname, name) == 0) {
        return i; 
      }
    }
  }
  return -1; 
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->unknown_ct++;
    return; 
  }
  ssize_t i = find_name_idx(c, name); 
  
  if (i < 0 ) {
    size_t name_lg = strlen(name) + 1;
    c->ct = realloc(c->ct, (c->length + 1) * sizeof(*(c->ct)));
    c->ct[c->length] = malloc(sizeof(**(c->ct)));
    c->ct[c->length]->value = malloc(name_lg * sizeof(char)); 
    strcpy(c->ct[c->length]->value, name);
    c->ct[c->length]->count = 1;
    c->length++;
  }
  else {
    c->ct[i]->count++; 
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (size_t i=0; i<c->length; i++) {
    fprintf(outFile, "%s: %ld\n", c->ct[i]->value, c->ct[i]->count);
  }
  if (c->unknown_ct >0) {
    fprintf(outFile, "<unknown> : %ld\n", c->unknown_ct);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  if (c->ct == NULL) {
    free(c);
    return;
  }
  for (size_t i=0; i<c->length; i++) {
    free(c->ct[i]->value);
  }
  for (size_t i=0; i<c->length; i++) {
    free(c->ct[i]);
  }
  free(c->ct);
  free(c);
}
