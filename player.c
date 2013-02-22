#include "player.h"
#include "shoe.h"
#include "hand.h"
#include "fdio.h"

#define OUT 4

/* input: a player pointer
 * output: none
 * return: none
 * comments: initializes the player
 */
void player_init(player * foo)
{
    foo->cash = 0;
    foo->value1 = 0;
    foo->value2 = 0;
    hand_init(&(foo->one));
    hand_init(&(foo->two));
}


/* input: a player pointer, an int, and a character
 * output: none
 * return: none
 * comments: alters the players total cash
 */
void alter_cash(player * foo, int bar, char sign)
{
    if (sign == '+')
        foo->cash += bar;
    if (sign == '-')
        foo->cash -= bar;
}


/* input: a player pointer
 * output: none
 * return: none
 * comments: frees the memory used by the player structure
 */
void player_destroy(player * foo)
{
    hand_destory(&foo->one);
    hand_destory(&foo->two);
}


/* input: a player pointer and an int
 * output: none
 * return: none
 * comments: gets the players bet
 */
void player_bet(player * foo, int bar)
{
    hand_bet(&foo->one, bar);
    hand_bet(&foo->two, bar);
}


/* input: a player pointer
 * output: none
 * return: an int
 * comments: gives the players current cash
 */
int player_curcash(player * foo)
{
    return foo->cash;
}


/* input: a player pointer and a shoe pointer
 * output: none
 * return: none
 * comments: resets the player after a hand
 */
void player_reset(player * foo, shoe * bar)
{
    while (!hand_empty(&foo->one))
        take_card(bar, hand_deq(&foo->one));
    while (!hand_empty(&foo->two))
        take_card(bar, hand_deq(&foo->two));

    foo->value1 = 0;
    foo->value2 = 0;

    hand_init(&foo->one);
    hand_init(&foo->two);
}


/* input: a player pointer, a shoe pointer
 * output: various player info
 * return: an int determining if the player busted, split, stood, etc
 * comments: makes the player play
 */
int player_play(player * foo, shoe * sho)
{
    int rval = 0;
    int split = 0;
    int i = 0;
    
    for (i = 0; i < 2; ++i)
       hand_enq(&foo->one, deal_card(sho));     

    split = hand_play(&foo->one, sho, 0);

    if (split == 1)
    {
        int test;

        hand_enq(&foo->two, hand_deq(&foo->one));
        test = hand_play(&foo->one, sho, 1);
        foo->value1 = hand_value(&foo->one);
        if (test == 0)
        {
            fdprintf(OUT, "Busted!!\n");
            foo->value1 = 0;
        }

        test = hand_play(&foo->two, sho, 2);
        foo->value2 = hand_value(&foo->one);
        if (test == 0)
        {
            fdprintf(OUT, "Busted!!\n");
            foo->value2 = 0;
        }
        
        rval = 2;
    }
    if (split == 2)
    {
        foo->value1 = hand_value(&foo->one);
        rval = 1;
    }
    if (split == 3)
        rval = 3;

    return rval;
}


/* input: a player pointer
 * output: none
 * return: an int
 * comments: gives the value of the players first deck
 */
int player_value1(player * foo)
{
    int rval = 0;
    rval = foo->value1;
    return rval;
}


/* input: player pointer
 * output: none
 * return: an int
 * comments: gives the value of the players second deck
 */
int player_value2(player * foo)
{
    int rval = 0;
    rval = foo->value2;
    return rval;
}

/* input: player pointer
 * output: none
 * return: an int
 * comments: gives the value of the players first bet
 */
int get_bet1(player * foo)
{
    int rval = 0;
    rval = hand_givebet(&foo->one);
    return rval;
}

/* input: player pointer
 * output: none
 * return: an int
 * comments: gives the players bet on his econd hand
 */
int get_bet2(player * foo)
{
    int rval = 0;
    rval = hand_givebet(&foo->two);
    return rval;
}

