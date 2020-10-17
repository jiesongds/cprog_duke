#include <stdio.h>
#include <stdlib.h>


size_t maxSeq(int * array, size_t n){
  size_t bst_lng = 1;
  if (n == 0) {
    return 0;
  }
  if (n == 1) {
    return bst_lng;
  }

  int cur_low = array[0];
  size_t cur_bst_lng = 1;
  
  for (size_t i = 0; i < n; i++) {
    int cur_value = array[i];
    if ((i == n-1) && (bst_lng > cur_bst_lng)){
      cur_bst_lng = bst_lng;
    }
    else if (cur_value > cur_low){
      bst_lng++;
      cur_low = cur_value;
    }
    else {
      cur_low = cur_value;
      if (bst_lng > cur_bst_lng){
	cur_bst_lng = bst_lng;
      }
      bst_lng = 1;
    }
 }

  return cur_bst_lng;
}
