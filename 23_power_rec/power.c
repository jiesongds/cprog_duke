#include <stdio.h>
#include <stdlib.h>

unsigned power_helper(unsigned x, unsigned y, unsigned ans) {
  if (x == 0 && y!= 0) {
    return 0;
  }
  if (x ==0 && y == 0) {
    return 1;
  }

  if (y == 0){
    return ans;
  }

  return power_helper(x, y-1, x * ans);
}

unsigned power(unsigned x, unsigned y){
  return power_helper(x, y, 1);
}
