#include <stdio.h>
#include <stdlib.h>
#include <time.h>    // time()
#include <assert.h>
#include "deck.h"

/*struct deck_t{
  card_t ** cards;
  size_t n_cards;
  };*/

int com (card_t c1,card_t c2){
  if ((c1.value == c2.value) &&(c1.suit == c2.suit)) return 1;
  return 0;

}

void print_hand(deck_t * hand){
  //  printf("printing..........\n");
  int i = 0;
  for(i = 0;i < hand->n_cards;i++){
    print_card(*(hand->cards)[i]);
   }
}

int deck_contains(deck_t * d, card_t c) {
  size_t i = 0;
  for(i = 0;i < d->n_cards;i++){
    if((((d->cards)[i])->value) == c.value){
      if((((d->cards)[i])->suit) == c.suit){
	return 1;
      }
    }
  }
  
  return 0;
}
void swapp(deck_t *d,size_t x,size_t y){
  card_t * temp;  
  // printf("%ld  ,%ld\n",x,y);
    if(x != y){
    temp = (d->cards)[x];
    (d->cards)[x] =(d->cards)[y];
    (d->cards)[y] = temp;  
  }
}
void shuffle(deck_t * d){
  size_t num = 0,i = 0,y=0;
  //time_t t;
  //  srand((unsigned) time(&t));
  for(i = 0; i < d->n_cards; i++){
    y++;
    num =((rand() % (d->n_cards))); 
    // printf("i >> %ld,num >> %ld\n",i,num);
    swapp(d,i,num);
    }
  
}

void assert_full_deck(deck_t * d) {
  card_t ** card =d -> cards ;
  card_t c;
  int count;

  for (size_t i=0 ;i< d -> n_cards ;i++){
    c=**(card+i);
    count=0;
    for (size_t j=0 ;j< d -> n_cards ;j++){
      if(com(**(card+j), c)) count ++;
    }
    assert(count ==1);
  }
}

void add_card_to(deck_t * deck, card_t c){
  deck->cards = realloc(deck->cards,(deck->n_cards+1)*sizeof(*deck->cards));
  deck->cards[deck->n_cards] = NULL;
  deck->cards[deck->n_cards] = realloc(deck->cards[deck->n_cards],sizeof(*deck->cards[deck->n_cards]));
  deck->cards[deck->n_cards]->value = c.value;
  deck->cards[deck->n_cards]->suit = c.suit;
  deck->n_cards++;
}


card_t * add_empty_card(deck_t * deck){
  card_t empty_card = {0,0};
  add_card_to(deck, empty_card);
  return deck->cards[deck->n_cards - 1];
}

deck_t * make_deck_exclude(deck_t * excluded_cards){
  deck_t *d = malloc(sizeof(*d));
  d->cards = NULL;
  d->n_cards = 0;
  card_t temp_card = {0,0};
  for(int i = 0;i < 52;i++){
    temp_card = card_from_num(i);
    if(!deck_contains(excluded_cards,temp_card)){
      add_card_to(d,temp_card);
    }
  }
  // free_deck(excluded_cards);
  return d;
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands){
  deck_t * excluded_Cards = malloc(sizeof(*excluded_Cards));
  excluded_Cards->cards = NULL;
  excluded_Cards->n_cards = 0;
  for(int i = 0;i < n_hands;i++){
    for(int j = 0;j < hands[i]->n_cards;j++){
      add_card_to(excluded_Cards,*(hands[i]->cards[j]));
    }
  }

  return make_deck_exclude(excluded_Cards);
}

void free_deck(deck_t * deck){
  for(int i = 0;i < deck->n_cards;i++){
    free(deck->cards[i]);
  }
  free(deck->cards);
  free(deck);
}
