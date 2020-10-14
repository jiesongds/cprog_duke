#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "cards.h"


void assert_card_valid(card_t c) {

  assert(c.value >= 2);
  assert(c.value <= VALUE_ACE);
  assert(c.suit >= SPADES);
  assert(c.suit <= CLUBS); 
  
}

const char * ranking_to_string(hand_ranking_t r) {
  switch(r){
  case STRAIGHT_FLUSH:
    return "STRAIGHT_FLUSH";
  case FOUR_OF_A_KIND:
    return "FOUR_OF_A_KIND";
  case FULL_HOUSE:
    return "FULL_HOUSE";
  case FLUSH:
    return "FLUSH";
  case STRAIGHT:
    return "STRAIGHT";
  case THREE_OF_A_KIND:
    return "THREE_OF_A_KIND";
  case TWO_PAIR:
    return "TWO_PAIR";
  case PAIR:
    return "PAIR";
  case NOTHING:
    return "NOTHING";
  }
  return "";
}

char value_letter(card_t c) {
  char outletter;
  if (c.value < 10){
    outletter = '0' + c.value;
    return outletter;
  }
  else if (c.value == 10) {
    return '0';
  }
  else if (c.value == VALUE_JACK) {
    return 'J';
  }
  else if (c.value == VALUE_QUEEN) {
    return 'Q';
  }
  else if (c.value == VALUE_KING) {
    return 'K';
  }
  else if (c.value == VALUE_ACE) {
    return 'A';
  }
  return 'x';
}


char suit_letter(card_t c) {
  if (c.suit == SPADES){
    return 's';
  }
  else if (c.suit == HEARTS){
    return 'h';
  }
  else if (c.suit == DIAMONDS){
    return 'd';
  }
  else if (c.suit == CLUBS){
    return 'c';
  }
  return 'x';
}

void print_card(card_t c) {
  printf("%c%c", value_letter(c), suit_letter(c));
}

card_t card_from_letters(char value_let, char suit_let) {
  card_t temp;
  if (value_let == 'J'){
    temp.value = VALUE_JACK;
  }
  else if (value_let == 'Q'){
    temp.value = VALUE_QUEEN;
  }
  else if (value_let == 'K'){
    temp.value = VALUE_KING;
  }
  else if (value_let == 'A'){
    temp.value = VALUE_ACE;
  }
  else if (value_let == '0'){
    temp.value = 10;
  }
  else{
    char value_l = value_let;
    int let_value = value_1 - '0';
    temp.value = let_value;
  }

  if (suit_let == 's'){
    temp.suit = SPADES;
  }
  else if (suit_let == 'h'){
    temp.suit = HEARTS;
  }
  else if (suit_let == 'd'){
    temp.suit = DIAMONDS;
  }
  else if (suit_let == 'c'){
    temp.suit = CLUBS;
  }
  else{
    temp.suit = NUM_SUITS;
  }

  assert_card_valid(temp);
  
  return temp;
}

card_t card_from_num(unsigned c) {
  card_t temp;
  return temp;
}


