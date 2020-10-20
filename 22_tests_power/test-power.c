#include <stdio.h>
#include <stdlib.h>

unsigned power (unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned cor_ans) {
  unsigned c = power(x, y);
  if (c != cor_ans) {
    //printf("some errors occurs");
    exit(EXIT_FAILURE);
  }
}

int main() {
  unsigned x = 0;
  unsigned y = 100;
  run_check(x, y, 0);

  x = 100;
  y = 0;
  run_check(x, y, 1);

  int  x1 = -3;
  y = 2;
  run_check(x1, y, 9);

  x = 0;
  y = 0;
  run_check(x, y, 1);

  x = 1;
  y = 100;
  run_check(x, y, 1);

  int x2 = -3;
  y = 3;
  run_check(x2, y, -27);

  x = 1;
  y = 1;
  run_check(x, y, 1);
  
  return EXIT_SUCCESS;
}
