#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void main() {

  int ar1[] = {1,2,3};
  size_t t1;
  t1 = maxSeq(ar1, 3);
  if (t1 != 3) {
    // printf("some errors occur");
    exit(EXIT_FAILURE);
  }

  int ar2[] = {-1000, -3,-2,0, -9, -8};
  size_t t2;
  t2 = maxSeq(ar2, 4);
  if (t2 != 4) {
    //printf("some errors occur");
    exit(EXIT_FAILURE);
  }

  int ar3[] = {};
  size_t t3;
  t3 = maxSeq(ar3, 0);
  if (t3 != 0) {
    //printf("some errors occur");
    exit(EXIT_FAILURE);
  }

  int ar4[] = {0, 0,0,0, 0, 0, 0, 0, 0, 0};
  size_t t4;
  t4 = maxSeq(ar4, 10);
  if (t4 != 1) {
    //printf("some errors occur");
    exit(EXIT_FAILURE);
  }

  int ar5[] = {-1000000000, -3,-2,0, 10000000};
  size_t t5;
  t5 = maxSeq(ar5, 5);
  if (t5 != 5) {
    //printf("some errors occur");
    exit(EXIT_FAILURE);
  }

  int ar6[] = {1, 1, 1,1};
  size_t t6;
  t6 = maxSeq(ar6, 4);
  if (t6 != 1) {
    //printf("some errors occur");
    exit(EXIT_FAILURE);
  }

  int ar7[] = {9, 8, 7, 6, 5, 4};
  size_t t7;
  t7 = maxSeq(ar7, 6);
  if (t7 != 1) {
    //printf("some errors occur");
    exit(EXIT_FAILURE);
  }

  unsigned int ar8[] = {300, -3, -2, -1, 3, 5, 2,1};
  size_t t8;
  t8 = maxSeq(ar8, 8);
  if (t8 != 5) {
    //printf("some errors occur");
    exit(EXIT_FAILURE);
  }

  int ar9[] = {5, 6, 7, 7, 7, 8, 9, 2, 3};
  size_t t9;
  t9 = maxSeq(ar9, 9);
  if (t9 != 3) {
    //printf("some errors occur");
    exit(EXIT_FAILURE);
  }  

  int ar10[] = {3, 2, 1, 1, 4, 5, 8, 9, 10, -2, -1};
  size_t t10;
  t10 = maxSeq(ar10, 11);
  if (t10 != 6) {
    //printf("some errors occur");
    exit(EXIT_FAILURE);
  }

  int ar11[] = {1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
  size_t t11;
  t11 = maxSeq(ar11, 10);
  if (t11 != 4) {
    //printf("some errors occur");
    exit(EXIT_FAILURE);
  }

  int ar12[] = {1, 12, 9, 17, 15, 33, 10, 44, 20, 99};
  size_t t12;
  t12 = maxSeq(ar12, 10);
  if (t12 != 2) {
    //printf("some errors occur");
    exit(EXIT_FAILURE);
  }

  int ar13[] = {-3, -42, -99, -1000, -999, -88, -77};
  size_t t13;
  t13 = maxSeq(ar13, 7);
  if (t13 != 4) {
    //printf("some errors occur");
    exit(EXIT_FAILURE);
  }


  
  exit(EXIT_SUCCESS);
 
}
