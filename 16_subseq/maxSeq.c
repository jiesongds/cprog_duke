#include <stdio.h>
#include <stdlib.h>


size_t maxSeq(int *array, size_t n){
  size_t bst_lng = 1;
  if (n == 0) {
    return 0;
  }
  if (n == 1) {
    return bst_lng;
  }

  size_t cur_bst_lng = 1;
  int cur_low = array[0];
  
  for (size_t i = 1; i < n; i++) {
    //if ((i == n-1) && (bst_lng > cur_bst_lng)){
    //cur_bst_lng = bst_lng;
    //}
    int cur_value = array[i];
    if (cur_value > cur_low){
      bst_lng++;
      if ((i == n-1) && bst_lng > cur_bst_lng){
	cur_bst_lng = bst_lng;
      }
    }
    else{
      if (bst_lng > cur_bst_lng){
	cur_bst_lng = bst_lng;
      }
      bst_lng = 1;
    }
    cur_low = cur_value;
    //else if (array[i+1] > array[i]){
    //bst_lng++;
    //}
    //else {
    //if (bst_lng > cur_bst_lng){
    //cur_bst_lng = bst_lng;
    //}
    //bst_lng = 1;
    //}
 }

  return cur_bst_lng;
}
