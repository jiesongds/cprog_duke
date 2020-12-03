#include <stdio.h>
#include <stdlib.h>
#include "cards.h"
#include "deck.h"
#include "eval.h" 

 

int main() {
    card_t c1 = card_from_num(3); 
    card_t c2 = card_from_num(22);
    card_t c3 = card_from_num(16);
    card_t c4 = card_from_num(32);
    card_t c5 = card_from_num(44);
    card_t c6 = card_from_num(10);
    deck_t * dk; 
    dk = malloc(sizeof(*dk)); 
    dk->n_cards = 0;
    dk->cards = NULL;
    add_card_to(dk, c1);
    add_card_to(dk, c2);
    add_card_to(dk, c3); 
    add_card_to(dk, c4); 
    add_card_to(dk, c5); 
    add_card_to(dk, c6);  

    deck_t * full = make_deck_exclude(dk);

    for (size_t i = 0; i<full->n_cards; i++) {
        print_card(*(full->cards[i]));
        printf("\t");   
    }

    printf("\n"); 

    //test the get_match_counts function 
    //if wanting to test the follwing function 
    //please turn on sort_hand and get_match_counts 
    //function procotypes in eval.h 
    
    //sort_hand(dk);
    //unsigned * counts = get_match_counts(dk); 
    
    //for (size_t i = 0; i<dk->n_cards; i++) {
        //print_card(*(dk->cards[i]));
        //printf("\t");
    //}

    //printf("\n");

    //for (size_t i = 0; i<dk->n_cards; i++) {
        //printf("%d\t", counts[i]);
    //}
    
    //printf("\n");

    //free(counts);
    free_deck(dk);
    free_deck(full);

    return EXIT_SUCCESS;
}