#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_hand(deck_t * hand){
  card_t **card_ptr = hand->cards;
  size_t ncards = hand->n_cards;
  for (size_t i =0; i<ncards; i++) {
    print_card(**card_ptr);
    printf(" ");
    card_ptr++;
  }
}

int deck_contains(deck_t * d, card_t c) {
  card_t **card_ptr = d->cards;
  size_t ncards = d->n_cards;
  for (size_t i = 0; i < ncards; i++){
    card_t checked_c = **card_ptr;
    if (checked_c.value == c.value && checked_c.suit == c.suit) {
      return 1;
    }
    card_ptr++;
  }
  return 0;
}

void shuffle(deck_t * d){
  card_t **card_ptr = d->cards;
  int ncards = d->n_cards;
 
 
  //size_t up = ncards-1;

  //if (ncards % 2 ==0){
    //ncards = ncards-1;
    //}
  
  for (int k=0; k < ncards; k++) {
    int rd_off = rand()%ncards;
    while (rd_off == k) {
      rd_off = rand()%ncards;
      }
    card_t *temp = card_ptr[k];
    card_ptr[k] = card_ptr[rd_off];
    card_ptr[rd_off] = temp;
    }
   
}

void assert_full_deck(deck_t * d) {

  card_t **card_ptr = d->cards;
  card_t **tem;
  size_t ncards = d->n_cards;
  int count;
  for (size_t i = 0; i < ncards; i++) {
    card_t c = **card_ptr;
    count = 0;
    tem = d->cards;
    for (size_t j = 0; j < ncards; j++){
      card_t ch = **tem;
      if (ch.value == c.value && ch.suit == c.suit) {
	count++;
      }
      tem++;
      
    }
    card_ptr++;
    assert(count == 1);
  }
}
