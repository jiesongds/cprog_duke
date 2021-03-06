#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"


int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Please provide an input file\n");
        return EXIT_FAILURE; 
    }

    FILE * f = fopen(argv[1], "r");
    size_t n_hand = 0; 
    future_cards_t * fc;
    fc = malloc(sizeof(*fc));
    fc->n_decks = 0;
    fc->decks=NULL; 
    deck_t ** read_hands = read_input(f, &n_hand, fc);

    for (size_t i=0; i<n_hand;i++) {
        print_hand(read_hands[i]);
        printf("\n");
    }

    for (size_t i=0; i<fc->n_decks; i++) {
        print_hand(&fc->decks[i]);
        printf("\n");
    }

    deck_t * full;
    full = malloc(sizeof(*full));
    full->n_cards = 0;
    full->cards = NULL; 
    for (size_t i = 0; i<52; i++) {
        card_t c = card_from_num(i);
        add_card_to(full, c);
    }

    shuffle(full);
    shuffle(full);

    print_hand(full);

    printf("\n"); 

    future_cards_from_deck(full, fc); 

    for (size_t i=0; i<n_hand;i++) {
        print_hand(read_hands[i]);
        printf("\n");
    }

    for (size_t i = 0; i<fc->n_decks; i++) {
        free(fc->decks[i].cards); 
    }
    free(fc->decks);
    free(fc); 

    for (size_t i=0; i<n_hand;i++) {
        free_deck(read_hands[i]);
    }

    free(read_hands); 
    free_deck(full); 

    if (fclose(f) != 0) {
        fprintf(stderr, "Could not close the file\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}