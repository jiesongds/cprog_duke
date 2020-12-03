#include "eval.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int card_ptr_comp(const void * vp1, const void * vp2) {
  const card_t * const * cp1 = vp1;
  const card_t * const * cp2 = vp2;
  card_t c1 = **cp1;
  card_t c2 = **cp2;
  if (c1.value != c2.value) {
    return -(c1.value - c2.value);
  }
  else{
    return (c2.suit - c1.suit);
  }
  return 0;
}

void sort_hand(deck_t * hand) {
  card_t **cards = hand->cards;
  size_t ncards = hand->n_cards;
  qsort(cards, ncards, sizeof(const card_t *), card_ptr_comp);
}

suit_t flush_suit(deck_t * hand) {
  size_t ncard = hand->n_cards;
  int ns = 0;
  int nh = 0;
  int nd = 0;
  int nc = 0; 
  for (size_t i=0; i<ncard; i++) {
    if (hand->cards[i]->suit == SPADES) {
      ns++;
    }
    else if (hand->cards[i]->suit == HEARTS) {
      nh++;
    }
    else if (hand->cards[i]->suit == DIAMONDS) {
      nd++;
    }
    else if (hand->cards[i]->suit == CLUBS) {
      nc++;
    }
  }
  if (ns >= 5) {
    return SPADES;}
  if (nh >= 5) {
    return HEARTS;}
  if (nd >= 5) {
    return DIAMONDS;}
  if (nc >= 5) {
    return CLUBS;}
  return NUM_SUITS;
}

unsigned get_largest_element(unsigned * arr, size_t n) {
  unsigned cur_max = arr[0];
  unsigned fin_max = arr[0];
  for (size_t i=0; i<n; i++) {
    if (i == n-1) {
      if (cur_max > fin_max){
	fin_max = cur_max;}
    }
    else if (arr[i+1] > arr[i]) {
      cur_max = arr[i+1];
    }   
  }
  return fin_max;
}

size_t get_match_index(unsigned * match_counts, size_t n,unsigned n_of_akind){
  for (size_t i = 0; i < n; i++) {
    if (match_counts[i] == n_of_akind) {
      return i;
    }
  }
  int matches = 0;
  for (size_t j=0; j<n; j++) {
    if (match_counts[j] == n_of_akind) {
      matches++;
    }
  }
  assert(matches > 0);
  return 0;
}

ssize_t  find_secondary_pair(deck_t * hand,
			     unsigned * match_counts,
			     size_t match_idx) {
  card_t **cards = hand->cards;
  size_t ncards = hand->n_cards;
  card_t org_card = **(cards + match_idx);
  for (ssize_t i = 0; i < ncards; i++) {
    if (match_counts[i] > 1) {
      card_t cc = **cards;
      if (cc.value != org_card.value) {
	return i;
      }
    }
    cards++;
  }
  return -1;
}

int is_ace_low_straight_at(deck_t * hand, size_t index, suit_t fs){
  size_t ncards = hand->n_cards;
  int is_five = 0;
  size_t marker;

  for (size_t i = index+1; i<ncards; i++){
    if(hand->cards[i]->value == 5){
      is_five++;
    }
  }
  if (is_five == 0 ){
    return 0;}
  for (size_t j = index+1; j<ncards; j++){
    if (hand->cards[j]->value == 5) {
      marker = j;
      break; 
    }
  }

  int counter = 1;
  size_t idx = marker;
  if (fs == NUM_SUITS){
    for (size_t k = idx; k<ncards;k++){
      if (k == ncards - 1){
	if (counter>=4){
	  return 1;}
	else {
	  return 0;}
      }
      else if (hand->cards[k]->value == hand->cards[k+1]->value+1){
	counter++;}
    }
  }
  else if (hand->cards[index]->suit != fs){
    marker = 0;
    return 0;}
  else {
    unsigned cv = hand->cards[marker]->value;
    for (size_t k = idx+1; k<ncards; k++){
      if ((cv == hand->cards[k]->value +1 ) &&
	  (hand->cards[k]->suit == fs)){
	counter++;
	cv = hand->cards[k]->value;
      }
    }
  }
  if (counter>=4) {
    return 1;}
  else {
    return 0;
  }
}

int is_n_length_straight_at(deck_t * hand, size_t index, suit_t fs, int n){
  if (n == 4){
    int str_at = is_ace_low_straight_at(hand, index, fs);
    return str_at;
  }
  else {
    size_t ncards = hand->n_cards;
    int counter = 1;
    if (fs == NUM_SUITS){
      unsigned cv = hand->cards[index]->value;
      for (size_t i = index+1; i < ncards; i++){
	if (cv == hand->cards[i]->value + 1){
	  counter++;
	  cv = hand->cards[i]->value;
	}
      }
      if (counter>=5) {
	return 1;}
    }
    else if (hand->cards[index]->suit != fs) {
      return 0;
    }
    else {
      unsigned cv = hand->cards[index]->value;
      for (size_t i = index+1; i < ncards; i++){
	 if ((cv == hand->cards[i]->value + 1) &&
	      (hand->cards[i]->suit == fs)){
	    counter++;
	    cv = hand->cards[i]->value;
	  }
	}
      if (counter>=5) {
	return 1;
      }
    }
  }
  return 0;
}

int is_straight_at(deck_t * hand, size_t index, suit_t fs) {
  card_t **cards = hand->cards;
  card_t cc = **(cards + index);
  if (cc.value == VALUE_ACE) {
    int n = 4;
    int str_at = is_n_length_straight_at(hand, index, fs, n);
    if (str_at == 1) {
      return -1;}
    else {
      n = 5;
      int str_at_n = is_n_length_straight_at(hand, index, fs, n);
      return str_at_n;
    }
  }
  else {
    int n = 5;
    int str_at = is_n_length_straight_at(hand, index, fs, n);
    return str_at;
  }
}

hand_eval_t build_hand_from_match(deck_t * hand,
				  unsigned n,
				  hand_ranking_t what,
				  size_t idx) {

  hand_eval_t ans;
  
  ans.ranking = what;

  if (what == NOTHING){
    for (size_t t=0; t<5; t++){
      ans.cards[t] = hand->cards[t];
    }
    return ans;
  }
  
  size_t i = 0;
  for (size_t j = idx; j < (idx + n); j++){
    ans.cards[i] = hand->cards[j];
    i++;
  }
  size_t k = n;
  size_t m = 0;
  while (k<5) {
    if (hand->cards[m]->value != hand->cards[idx]->value) {
      ans.cards[k] = hand->cards[m];
      k++;
      m++;
    }
    else{
      m++;
    }
  }
  
  return ans;
}


int compare_hands(deck_t * hand1, deck_t * hand2) {

  sort_hand(hand1);
  sort_hand(hand2);

  hand_eval_t h1 = evaluate_hand(hand1);
  hand_eval_t h2 = evaluate_hand(hand2);

  //printf("%s, hand 1\n", ranking_to_string(h1.ranking));
  //printf("%s, hand 2\n", ranking_to_string(h2.ranking));
  
  if (h1.ranking < h2.ranking) {
    return 1;
  }
  else if (h1.ranking > h2.ranking) {
    return -1;
  }
  else {
    size_t idx = 0;
    while (idx<5){
      if (h1.cards[idx]->value == h2.cards[idx]->value){
	//printf("%d\n", h1.cards[idx]->value);
	idx++;
      }
      else if (h1.cards[idx]->value > h2.cards[idx]->value){
	return 1;
      }
      else {
	return -1;
      }
      }
  }
  
  return 0;
}

//You will write this function in Course 4.
//For now, we leave a prototype (and provide our
//implementation in eval-c4.o) so that the
//other functions we have provided can make
//use of get_match_counts.
unsigned * get_match_counts(deck_t * hand) {
  unsigned * counts;
  counts = malloc((hand->n_cards) * sizeof(*counts));
  for (size_t i = 0; i<hand->n_cards; i++) {
    counts[i] = 1;
  }

  unsigned cur_value = hand->cards[0]->value;
  unsigned cur_counter = 0; 
  for (size_t i = 0; i<hand->n_cards; i++) {
    if (i == (hand->n_cards - 1)) {
      if (hand->cards[i]->value == cur_value) {
        cur_counter++;
        counts[i] = cur_counter;
      }
      else {
        counts[i-1] = cur_counter;
        counts[i] = 1;
      }
    }
    else if (hand->cards[i]->value == cur_value) {
      cur_counter++;
    }
    else {
      counts[i-1] = cur_counter;
      cur_counter = 1;
      cur_value = hand->cards[i]->value;
    }
  }

  for (size_t i = 0; i<hand->n_cards; i++) {
    if (counts[i] > 1) {
      size_t idx = i;
      for (size_t j = 1; counts[i] - j > 0; j++) {
        counts[idx - j] = counts[i];
      }
    }
  }
  return counts; 
}

// We provide the below functions.  You do NOT need to modify them
// In fact, you should not modify them!


//This function copies a straight starting at index "ind" from deck "from".
//This copies "count" cards (typically 5).
//into the card array "to"
//if "fs" is NUM_SUITS, then suits are ignored.
//if "fs" is any other value, a straight flush (of that suit) is copied.
void copy_straight(card_t ** to, deck_t *from, size_t ind, suit_t fs, size_t count) {
  assert(fs == NUM_SUITS || from->cards[ind]->suit == fs);
  unsigned nextv = from->cards[ind]->value;
  size_t to_ind = 0;
  while (count > 0) {
    assert(ind < from->n_cards);
    assert(nextv >= 2);
    assert(to_ind <5);
    if (from->cards[ind]->value == nextv &&
	(fs == NUM_SUITS || from->cards[ind]->suit == fs)){
      to[to_ind] = from->cards[ind];
      to_ind++;
      count--;
      nextv--;
    }
    ind++;
  }
}


//This looks for a straight (or straight flush if "fs" is not NUM_SUITS)
// in "hand".  It calls the student's is_straight_at for each possible
// index to do the work of detecting the straight.
// If one is found, copy_straight is used to copy the cards into
// "ans".
int find_straight(deck_t * hand, suit_t fs, hand_eval_t * ans) {
  if (hand->n_cards < 5){
    return 0;
  }
  for(size_t i = 0; i <= hand->n_cards -5; i++) {
    int x = is_straight_at(hand, i, fs);
    if (x != 0){
      if (x < 0) { //ace low straight
	assert(hand->cards[i]->value == VALUE_ACE &&
	       (fs == NUM_SUITS || hand->cards[i]->suit == fs));
	ans->cards[4] = hand->cards[i];
	size_t cpind = i+1;
	while(hand->cards[cpind]->value != 5 ||
	      !(fs==NUM_SUITS || hand->cards[cpind]->suit ==fs)){
	  cpind++;
	  assert(cpind < hand->n_cards);
	}
	copy_straight(ans->cards, hand, cpind, fs,4) ;
      }
      else {
	copy_straight(ans->cards, hand, i, fs,5);
      }
      return 1;
    }
  }
  return 0;
}


//This function puts all the hand evaluation logic together.
//This function is longer than we generally like to make functions,
//and is thus not so great for readability :(
hand_eval_t evaluate_hand(deck_t * hand) {
  suit_t fs = flush_suit(hand);
  hand_eval_t ans;
  if (fs != NUM_SUITS) {
    if(find_straight(hand, fs, &ans)) {
      ans.ranking = STRAIGHT_FLUSH;
      return ans;
    }
  }
  unsigned * match_counts = get_match_counts(hand);
  unsigned n_of_a_kind = get_largest_element(match_counts, hand->n_cards);
  assert(n_of_a_kind <= 4);
  size_t match_idx = get_match_index(match_counts, hand->n_cards, n_of_a_kind);
  ssize_t other_pair_idx = find_secondary_pair(hand, match_counts, match_idx);
  free(match_counts);
  if (n_of_a_kind == 4) { //4 of a kind
    return build_hand_from_match(hand, 4, FOUR_OF_A_KIND, match_idx);
  }
  else if (n_of_a_kind == 3 && other_pair_idx >= 0) {     //full house
    ans = build_hand_from_match(hand, 3, FULL_HOUSE, match_idx);
    ans.cards[3] = hand->cards[other_pair_idx];
    ans.cards[4] = hand->cards[other_pair_idx+1];
    return ans;
  }
  else if(fs != NUM_SUITS) { //flush
    ans.ranking = FLUSH;
    size_t copy_idx = 0;
    for(size_t i = 0; i < hand->n_cards;i++) {
      if (hand->cards[i]->suit == fs){
	ans.cards[copy_idx] = hand->cards[i];
	copy_idx++;
	if (copy_idx >=5){
	  break;
	}
      }
    }
    return ans;
  }
  else if(find_straight(hand,NUM_SUITS, &ans)) {     //straight
    ans.ranking = STRAIGHT;
    return ans;
  }
  else if (n_of_a_kind == 3) { //3 of a kind
    return build_hand_from_match(hand, 3, THREE_OF_A_KIND, match_idx);
  }
  else if (other_pair_idx >=0) {     //two pair
    assert(n_of_a_kind ==2);
    ans = build_hand_from_match(hand, 2, TWO_PAIR, match_idx);
    ans.cards[2] = hand->cards[other_pair_idx];
    ans.cards[3] = hand->cards[other_pair_idx + 1];
    if (match_idx > 0) {
      ans.cards[4] = hand->cards[0];
    }
    else if (other_pair_idx > 2) {  //if match_idx is 0, first pair is in 01
      //if other_pair_idx > 2, then, e.g. A A K Q Q
      ans.cards[4] = hand->cards[2];
    }
    else {       //e.g., A A K K Q
      ans.cards[4] = hand->cards[4];
    }
    return ans;
  }
  else if (n_of_a_kind == 2) {
    return build_hand_from_match(hand, 2, PAIR, match_idx);
  }
  return build_hand_from_match(hand, 0, NOTHING, 0);
}
