#include <stdlib.h>

#include "cardq.h"
#include "card.h"
#include "fdio.h"

#define OUT 4

/* input: a cardq pointer
 * output: none
 * return: none
 * comments: initializes the card queue
 */
void cardq_init(cardq * q)
{
    q->size = 10;
    q->arr = (card *)malloc((q->size)*sizeof(card));
    q->back =  0;
    q->slide = 0;
}

/* input: a cardq pointer
 * output: none
 * return: an int
 * comments: tells if the card queue is emtpy
 */
int cardq_empty(cardq * q)
{
    return (q->back <= 0);
}

/* input: a cardq pointer
 * output: none
 * return: none
 * comments: tells if the card queue is full
 */
int cardq_full(cardq  * q)
{
    return (q->back >= q->size);
}

/* input: a cardq pointer, a card
 * output: none
 * return: none
 * comments: adds a number to the queue
 */
void cardq_enq(cardq * q, card foo)
{
    if(cardq_full(q))
    {
        q->size += 10;
        q->arr = (card *)realloc(q->arr, (q->size)*sizeof(card));
    }
    q->arr[q->back++] = foo;
}

/* input: a cardq pointer
 * output: none
 * return: a card
 * comments: removes a number from the queue and returns it
 */
card cardq_deq(cardq * q)
{
    int i;
    card rval = q->arr[0];
    if (cardq_empty(q))
    {
        fdprintf(OUT, "deq error, exiting.....\n");
        exit(1);
    }
    for (i = 1; i < (q->back); ++i)
        q->arr[i - 1] = q->arr[i];
    --(q->back);
    --(q->slide);
    return rval;
}

/* input: a cardq pointer
 * output: none
 * return: none
 * comments: destroys the card queue
 */
void cardq_destroy(cardq * q)
{
    free(q->arr);
}

/* input: a cardq pointer
 * output: none
 * return: an int
 * comments: gives the length of the card queue
 */
int cardq_length(cardq * q)
{
    return q->back;
}


/* input: a cardq pointer
 * output: none
 * return: none
 * comments: sets the position of the slide
 */
void cardq_slideset(cardq * q)
{
    q->slide = q->back;
}


/* input: a cardq pointer
 * output: none
 * return: an int
 * comments: gives the position of the slide
 */
int cardq_slidespot(cardq * q)
{
    return q->slide;
}

