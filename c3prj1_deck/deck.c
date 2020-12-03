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

  for (int k=0; k < ncards; k++) {
    int rd_off = rand()%ncards;
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

void add_card_to(deck_t * deck, card_t c) {
  deck->cards = realloc(deck->cards, (deck->n_cards + 1) * sizeof(*(deck->cards)));
  deck->cards[deck->n_cards] = malloc(sizeof(**(deck->cards)));
  *(deck->cards[deck->n_cards]) = c; 
  deck->n_cards = deck->n_cards + 1; 
}

card_t * add_empty_card(deck_t * deck) {
  card_t c;
  c.suit = 0;
  c.value = 0; 
  add_card_to(deck, c);
  card_t * ptr = deck->cards[deck->n_cards-1]; 
  return ptr; 
}

deck_t * make_deck_exclude(deck_t * excluded_cards) {
  deck_t * dk; 
  dk = malloc(sizeof(*dk)); 
  dk->n_cards = 0;
  dk->cards = NULL;
  for (unsigned c=0; c<52; c++) {
    card_t ct = card_from_num(c); 
    if (!deck_contains(excluded_cards, ct)) {
      add_card_to(dk, ct); 
    }
  }
  return dk;
}

void free_deck(deck_t * deck) {
  for (size_t i = 0; i<deck->n_cards; i++) {
    free(deck->cards[i]);
  }
  free(deck->cards);
  free(deck); 
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands) {
  deck_t * ex_dk;
  ex_dk = malloc(sizeof(*ex_dk)); 
  ex_dk->n_cards = 0;
  ex_dk->cards = NULL;  

  for (size_t i=0; i<n_hands; i++) {
    deck_t * hand = hands[i];
    for (size_t j = 0; j<hand->n_cards; j++) {
      card_t c = *(hand->cards[j]);
      add_card_to(ex_dk, c);
    }
  }

  deck_t * dk = make_deck_exclude(ex_dk);
  free_deck(ex_dk); 
  return dk; 
}


