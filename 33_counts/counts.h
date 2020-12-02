#ifndef __COUNTS_H__
#define __COUNTS_H__
struct _one_count_t {
  //DEFINE ME
  char * value; 
  size_t count; 
};
typedef struct _one_count_t one_count_t;

struct _counts_t {
  //DEFINE ME
  one_count_t ** ct; 
  size_t length; 
  size_t unknown_ct; 
};
typedef struct _counts_t counts_t;

counts_t * createCounts(void);
ssize_t find_name_idx(counts_t * c, const char * name); 
void addCount(counts_t * c, const char * name);
void printCounts(counts_t * c, FILE * outFile);

void freeCounts(counts_t * c);

#endif
