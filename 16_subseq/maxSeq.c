#include <stdio.h>
#include <stdlib.h>


size_t maxSeq(int * array, size_t n){
  size_t ans = 1;
  if (n == 0) {
    return 0;
  }
  if (n == 1) {
    return ans;
  }

  size_t bst_lng = ans;
  int cur_low = array[0];
  
  for (size_t i = 1; i < n; i++) {
    int cur_value = array[i];
    if (cur_value > cur_low){
      ans++;
      cur_low = cur_value;
      bst_lng = ans;
    }
    else {
      cur_low = cur_value;
      ans = 1;
    }
 }

  return bst_lng;
}
