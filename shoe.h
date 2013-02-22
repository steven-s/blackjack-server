#ifndef SHOE_H
#define SHOE_H

#include "cardq.h"

typedef struct st_shoe
{
    cardq sho;
}shoe;

void shoe_init(shoe *);
void shoe_create(shoe *, int);
card deal_card(shoe *);
void take_card(shoe *, card);
void shoe_shuffle(shoe *);
void shoe_destroy(shoe *);
int shoe_size(shoe *);

#endif
