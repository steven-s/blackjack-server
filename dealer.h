/* Steven Samson
 * CSCI 1840
 */

#ifndef DEALER_H
#define DEALER_H

#include "hand.h"
#include "shoe.h"

typedef struct st_dealer
{
    hand one;
    int value;
    int cnt;
}dealer;

void dealer_init(dealer *);
int dealer_play(dealer *, shoe *);
int dealer_value(dealer *);
void dealer_destroy(dealer *);
int dealer_start(dealer *, shoe *);
void dealer_reset(dealer *, shoe *);

#endif
