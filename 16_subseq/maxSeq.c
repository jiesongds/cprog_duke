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

  size_t bst_lng = 1;
  int cur_low = array[0];
  size_t cur_bst_lng = 1;
  
  for (size_t i = 1; i < n; i++) {
    int cur_value = array[i];
    if (cur_value > cur_low){
      ans++;
      cur_low = cur_value;
      bst_lng = ans;
    }
    else {
      cur_low = cur_value;
      if (bst_lng > cur_bst_lng){
	cur_bst_lng = bst_lng;
      }
      ans = 1;
    }
 }

  return cur_bst_lng;
}
