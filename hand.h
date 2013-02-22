#ifndef HAND_H
#define HAND_H

#include "card.h"
#include "cardq.h"
#include "shoe.h"

typedef struct st_hand
{
    cardq han; /* holds the cards in the hand */
    int soft_cnt; /* counts the soft aces */
    int ace; /* determines the prescence of an ace */
    char * optstr; /* contains check for the option string */
    int bet; /* holds the bet */
    int bjack; /* holds a value to see if the hand has a blackjack */
    int value; /* contains the hands value */
}hand;

void hand_init(hand *); /* initializes the hand */
void hand_enq(hand *, card); /* adds a card to the hand */
card hand_deq(hand *); /* removes a card from the hand */
void hand_destory(hand *); /* destroys the hand */
void hand_print(hand *); /* prints the hand */
int hand_value(hand *); /* gives the hands total value */
int hand_length(hand *); /* gives the hand length */
int hand_empty(hand *); /* tells if the hand is empty */
void hand_bet(hand *, int); /* takes the bet */
int hand_givebet(hand *); /* gives the bet */
int hand_play(hand *, shoe *, int); /* plays a hand */
int hand_bjack(hand *); /* gives the value of bjack */

#endif
