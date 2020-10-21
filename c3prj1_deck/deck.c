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
  size_t ncards = d->n_cards;
  //card_t **temp = d->cards; // build a tem deck of cards 
  //for (size_t i = 0;  i < ncards; i++){
  //temp++;
  //}
  size_t up = ncards-1;
  for (size_t k=0; k < ncards; k++) {
    size_t rd_off = rand()%up;
    while (rd_off == k) {
      rd_off = rand()%up;
    }
    //printf("rand is %d\n", rd_off);
    //printf("current index is %ld\n", k);
    //card_t mycard = *card_ptr[k];
    //printf("current card value is %d\n", mycard.value);
    //print_card(mycard);
    //printf("\n");
    card_t *temp = card_ptr[k];
    card_ptr[k] = card_ptr[rd_off];
    //card_t mycard2 = *card_ptr[k];
    //print_card(mycard2);
    //printf("\n");
    card_ptr[rd_off] = temp;
  }




  //}
  
  //size_t k = 0;
  //for (size_t j = ncards-1; j >= 0; j--) {
  //int rd = rand() % 100;
  //if (rd >= 50 && k < ncards/2) {
  //card_t temp_c = **card_ptr;
      
  //print_card(temp_c);
      //printf(" ");
      //print_card(**temp);
      
      //**card_ptr = **temp;
      //size_t offset = j - k;
      //**card_ptr = **(card_ptr + offset);
      //print_card(**card_ptr);
      //printf(" ");
      //**(card_ptr + offset) = temp_c;
      //print_card(temp_c);
  //}
  //card_ptr++;
  //k++;
    //temp--;
  //}
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
