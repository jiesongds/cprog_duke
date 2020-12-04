#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

int main(int argc, char ** argv) {
  //YOUR CODE GOES HERE
  if (argc < 2) {
    fprintf(stderr, "Please provide at least an input list of hands\n");
    return EXIT_FAILURE;
  }
  int trials; 
  if (argc == 2) {
    trials = 10000;  
  }
  else {
    trials = atoi(argv[2]); 
  }

  FILE * f = fopen(argv[1], "r");
  if (f==NULL) {
    fprintf(stderr, "Could not open the file\n");
    return EXIT_FAILURE; 
  }

  size_t n_hands = 0;
  future_cards_t * fc;
  fc = malloc(sizeof(*fc)); //will be FREED!!!
  fc->n_decks = 0;
  fc->decks=NULL;
  deck_t ** readin_hands = read_input(f, &n_hands, fc);//will be FREED!!!
  deck_t * rem_deck = build_remaining_deck(readin_hands, n_hands);//be FREED!!!
  int * counts;
  counts = calloc((n_hands+1), sizeof(*counts));//will be FREED!!!

  for (int i=0; i<trials; i++) {
    shuffle(rem_deck);
    future_cards_from_deck(rem_deck, fc); 
    deck_t * cur_win_hand = readin_hands[0]; 
    size_t cur_win_idx = 0;
    size_t no_ties = 0; 
    for (size_t j=0; j<n_hands; j++) {
      if (compare_hands(cur_win_hand, readin_hands[j]) < 0) {
        cur_win_hand = readin_hands[j];
        cur_win_idx = j; 
      }
    }
    for (size_t j=0; j<n_hands; j++) {
      if (compare_hands(cur_win_hand, readin_hands[j]) == 0) {
        no_ties++;
      }
    }
    if (no_ties >= 2) {
      counts[n_hands]++;
    }
    else {
      counts[cur_win_idx]++;
    }
  }

  for (size_t i=0; i<n_hands; i++) {
    printf("Hand %zu won %u / %u times (%.2f%%)\n", i, counts[i], trials, 100 * (float) counts[i] / (float) trials);
  }
  printf("And there were %u ties\n", counts[n_hands]);

  //FREE fc!!!
  for (size_t i = 0; i<fc->n_decks; i++) {
        free(fc->decks[i].cards); 
    }
  free(fc->decks);
  free(fc); 

  for (size_t i=0; i<n_hands;i++) {
    free_deck(readin_hands[i]);
  }
  free(readin_hands);//FREE readin_hands!!!
  free_deck(rem_deck);//FREE rem_deck!!!
  free(counts);//FREE counts!!! 

  if (fclose(f) != 0) {
    fprintf(stderr, "Could not close the file\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
