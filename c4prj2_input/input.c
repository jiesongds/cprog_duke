#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "input.h"

void stripNewline(char * str) {
  char * p = strchr(str, '\n');
  if (p != NULL) {
    *p = '\0';
  }
}

void find_largest_n(char * line, int * largest_n) {
    char * token = strtok(line, " ");
    while( token !=NULL) {
        char * questionMark = strchr(token, '?');
        if (questionMark != NULL) {
            questionMark++;
            int cur_n = atoi(questionMark);
            if (cur_n > *largest_n) {
               *largest_n = cur_n; 
            }
        }
        token = strtok(NULL, " ");
    }
}

deck_t * hand_from_string(const char * str, future_cards_t * fc) {
    deck_t * ahand; 
    ahand = malloc(sizeof(*ahand));
    ahand->cards = NULL;
    ahand->n_cards = 0; 
    
    char * str_hp = malloc((strlen(str) + 1) * sizeof(*str_hp));
    strcpy(str_hp, str); 
    char * token = strtok(str_hp, " ");
    while(token != NULL) {
        char * questionMark = strchr(token, '?');
        if (questionMark == NULL) {
            card_t card = card_from_letters(token[0], token[1]);
            add_card_to(ahand, card); 
        }
        else {
            questionMark++;
            size_t index = atoi(questionMark);
            card_t * em_ptr = add_empty_card(ahand);
            add_future_card(fc, index, em_ptr); 
        }
        token = strtok(NULL, " "); 
    }
    free(str_hp);
    return ahand; 
}

deck_t ** read_input(FILE * f, size_t * n_hands, future_cards_t * fc) {
    if (f == NULL) {
       fprintf(stderr, "Empty file\n");
       return NULL;
    }

    deck_t ** rd_hds=NULL; 
    *n_hands = 0;

    char * line = NULL;
    size_t sz = 0; 
    int largest_n = -1; 

    while (getline(&line, &sz, f) >= 0 ) {
        stripNewline(line);
        find_largest_n(line, &largest_n); 
        free(line);
        line=NULL; 
    }
    free(line);
    line=NULL; 
    //printf("The largest n is %d\n", largest_n);
    if (largest_n >=0) {
        size_t capacity = largest_n; 
        if (capacity>=fc->n_decks) {
            fc->decks = realloc(fc->decks, (capacity+1) * sizeof(*(fc->decks))); 
            fc->n_decks = capacity + 1; 
            for (size_t i = 0; i<fc->n_decks; i++) {
                fc->decks[i].cards = NULL;
                fc->decks[i].n_cards = 0;  
            }
        }
    }
    if (largest_n<0) {
        largest_n = 0;
    } 
    rewind(f); 
    while (getline(&line, &sz, f) >= 0 ) {
        stripNewline(line);
        deck_t * ahand = hand_from_string(line, fc);
        if (ahand->n_cards<5) {
            fprintf(stderr, "Must have at least 5 cards\n");
            return NULL;
        }
        if (largest_n > ahand->n_cards) {
            fprintf(stderr, "Too many unknown cards\n");
            return NULL; 
        }
        rd_hds = realloc(rd_hds, (*n_hands + 1) * sizeof(*rd_hds));
        rd_hds[*n_hands] = ahand;
        *n_hands = *n_hands + 1;
        free(line);
        line=NULL; 
    }
    free(line);
    return rd_hds; 
}