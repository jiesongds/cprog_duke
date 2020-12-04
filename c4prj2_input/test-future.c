#include <stdio.h>
#include <stdlib.h>
#include "future.h"
#include "deck.h"
#include "cards.h"

int main() {
    future_cards_t * fc;
    fc = malloc(sizeof(*fc));
    fc->decks = NULL; 
    fc->n_decks = 0; 

    deck_t * h1; 
    h1 = malloc(sizeof(*h1)); 
    h1->cards = NULL;
    h1->n_cards = 0; 
    add_empty_card(h1);
    add_empty_card(h1); 

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

    card_t * p0 = h1->cards[0];
    card_t * p1 = h1->cards[1]; 

    add_future_card(fc, 1, p1);
    add_future_card(fc, 0, p0);

    print_hand(&(fc->decks[0]));
    printf("\n"); 
    print_hand(&(fc->decks[1]));
    printf("\n");

    future_cards_from_deck(full, fc);
    future_cards_from_deck(full, fc);

    print_hand(&(fc->decks[0]));
    printf("\n"); 
    print_hand(&(fc->decks[1]));
    printf("\n");

    for (size_t i = 0; i<fc->n_decks; i++) {
        free(fc->decks[i].cards); 
    }
    free(fc->decks);
    free(fc); 

    free_deck(h1);
    free_deck(full); 

    return EXIT_SUCCESS; 

}