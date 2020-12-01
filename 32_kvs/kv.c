#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"


//stripe newline \n from a string
void stripNewline(char * str) {
  char * p = strchr(str, '\n');
  if (p != NULL) {
    *p = '\0';
  }
}


//split the line and create a kvpair struct on the heap 
kvpair_t* getkypair(char* line) {
  kvpair_t* kvpair; 
  kvpair = malloc(sizeof(*kvpair));
  //printf("The read line is -> %s\n", line);

  const char equal = '=';
  char * eqls = strchr(line, equal);
  //printf("%s", eqls);
  eqls++; 
  char * value = eqls;
  //printf("%s\n", value); 
  stripNewline(value); 

  char * valueptr = value;
  size_t value_length = 0;
  while (*valueptr != '\0') {
    valueptr++;
    value_length++;
  }
  value_length++;
  kvpair->value = malloc(value_length * sizeof(*(kvpair->value)));
  strcpy(kvpair->value, value);
  //printf("The read value is -> %s\n", kvpair->value);
  //printf("The read value length is -> %ld\n", value_length);


  char* key = strtok(line, "=");
  //printf("%s\n", key);
  char* keyptr = key; 
  size_t key_length = 0;
  while (*keyptr != '\0') {
    keyptr++;
    key_length++;
  }
  key_length++;
  //printf("Key length is -> %ld\n", key_length);
  kvpair->key = malloc(key_length * sizeof(*(kvpair->key)));
  strcpy(kvpair->key, key);
  //printf("The read key is -> %s\n", kvpair->key);
  return kvpair;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE* f = fopen(fname, "r");
  if (f == NULL){
    fprintf(stderr, "Could not open the file\n");
    return NULL;
  }

  char* line = NULL; 
  size_t sz = 0; 

  kvarray_t* kvarray; 
  kvarray = malloc(sizeof(*kvarray)); 
  kvarray->length = 0; 
  kvarray->kv = NULL;

  while (getline(&line, &sz, f) >= 0) {
    kvpair_t* kvpair = getkypair(line); 
    kvarray->kv = realloc(kvarray->kv, (kvarray->length + 1) * sizeof(*(kvarray->kv)));
    kvarray->kv[kvarray->length] = kvpair;
    kvarray->length++;
    free(line);
    line = NULL;
  }
  free(line);
  if (fclose(f) != 0) {
    fprintf(stderr, "could not close the file\n");
    return NULL;
  }
  return kvarray;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i=0; i<pairs->length; i++) {
    free(pairs->kv[i]->key);
    free(pairs->kv[i]->value);
    free(pairs->kv[i]);
  }
  free(pairs->kv);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i=0; i<pairs->length; i++) {
    char * key = pairs->kv[i]->key; 
    char * value = pairs->kv[i]->value;
    printf("key = '%s' value = '%s'\n", key, value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i=0; i<pairs->length; i++) {
    char * search_key = pairs->kv[i]->key;
    if (strcmp(search_key, key) == 0) {
      return pairs->kv[i]->value;
    }
  }
  return NULL;
}
