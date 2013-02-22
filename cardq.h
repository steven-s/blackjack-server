/* A queue structure modified to hold cards */

#ifndef CARDQ_H
#define CARDQ_H

#include "cardq.h"
#include "card.h"

/* struct with the basic queue elements in it */
typedef struct cardq_st
{
    int back; /* keeps track of the back */
    int slide; /* keeps track of how many undelt cards are in the
                * cardq 
                */
    int size; /* stores the queue's size multiplier*/
    card * arr; /* pointer to the queue array */
}cardq;

int cardq_empty(cardq *); /* tells if emtpy */
int cardq_full(cardq *); /* tells if full */
void cardq_init(cardq *); /* initializes the queue */
void cardq_enq(cardq *, card); /* adds #'s to the queue */
card cardq_deq(cardq *); /* removes #'s from the queue */
void cardq_destroy(cardq *); /* destroys the queue */
int cardq_length(cardq *); /* gives the queue's length */
void cardq_slideset(cardq *); /* sets slide's spot */
int cardq_slidespot(cardq *); /* gives slides position */
card cardq_get(cardq *, int);

#endif

