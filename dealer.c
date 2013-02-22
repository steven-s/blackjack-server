#include "dealer.h"
#include "fdio.h"

#define OUT 4

/* input: a dealer pointer
 * output: none
 * return: none
 * comments: intitializes the dealer
 */
void dealer_init(dealer * foo)
{
    hand_init(&foo->one);
    foo->value = 0;
    foo->cnt = 0;
}


/* input: a dealer pointer, a shoe pointer
 * output: various dealer info
 * return: an int with the first cards value
 * comments: starts the dealer and shows the first card
 */
int dealer_start(dealer * foo, shoe * bar)
{
    int i;
    int rval = 0;
    card tmp;
    
    for (i = 0; i < 2; ++i)
    {
        card_init(&tmp);
        tmp = deal_card(bar);
        hand_enq(&foo->one, tmp);
        ++foo->cnt;
        foo->value += card_value(&tmp);
        if (i == 0)
        {
            fdprintf(OUT, "Dealer shows : ");
            card_print(&tmp);
            rval = card_value(&tmp);
            fdprintf(OUT, "\n");
        }
    }
    return rval;
}


/* input: a dealer pointer, a shoe pointer
 * output: none
 * return: none
 * comments: resets the dealer
 */
void dealer_reset(dealer * foo, shoe * bar)
{
    card tmp;
    card_init(&tmp);
    while (!hand_empty(&foo->one))
    {
        tmp = hand_deq(&foo->one);
        take_card(bar, tmp);
    }
    foo->value = 0;
    hand_init(&foo->one);
}


/* input: a dealer pointer
 * output: none
 * return: none
 * comments: frees the memory used by the dealer
 */
void dealer_destroy(dealer * foo)
{
    hand_destory(&foo->one);
}


/* input: a dealer pointer, a shoe pointer
 * output: various dealer info
 * return: an int on if the dealer had a blackjack or not
 * comments: makes the dealer play
 */
int dealer_play(dealer * foo, shoe * sho)
{
    int rval = 0;
    int x = 0;
    while (x != 1)
    {
        if ((dealer_value(foo) <= 16) && !x)
        {
            fdprintf(OUT, "Dealer has : ");
            hand_print(&foo->one); 
            
            hand_enq(&foo->one, deal_card(sho));
            
            fdprintf(OUT, " hit\n");

            foo->value = hand_value(&foo->one);
        }
        
        if ((dealer_value(foo) >= 17) && (dealer_value(foo) <= 21) && !x)
        {
            foo->value = hand_value(&foo->one);
            fdprintf(OUT, "Dealer has : ");
            hand_print(&foo->one);
            fdprintf(OUT, " stand\n");

            x = 1;
        }

        if ((dealer_value(foo) == 21) && (hand_length(&foo->one) <= 2))
            rval = 1;
        
        if ((dealer_value(foo) > 21) && !x)
        {
            fdprintf(OUT, "Dealer has : ");
            hand_print(&foo->one);
            fdprintf(OUT, "\n");
            fdprintf(OUT, "Dealer busts!\n");
            foo->value = 0;
            x = 1;
        }
    }/* end while x != 1 */

    return rval;
}


/* input: a dealer pointer
 * output: none
 * return: an int
 * comments: gives the value of the dealers hand
 */
int dealer_value(dealer * foo)
{
    return foo->value;
}

