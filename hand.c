#include <stdlib.h>
#include <string.h>

#include "hand.h"
#include "cardq.h"
#include "shoe.h"
#include "fdio.h"
#include "card.h"

void invalid(int, int, int);

#define OUT 4
#define IN 4

/* input: a hand pointer
 * output: none
 * return: none
 * comments: initializes the hands values
 */
void hand_init(hand * foo)
{
    cardq_init(&foo->han);
    foo->soft_cnt = 0;
    foo->ace = 0;
    foo->value = 0;
    foo->bet = 0;
    foo->bjack = 0;
    foo->optstr = "hdsp";
}


/* input: a hand pointer and a card
 * output: none
 * return: none
 * comments: adds a card to the hand and checks if the hand is soft or
 * not
 */
void hand_enq(hand * foo, card bar)
{
    cardq_enq(&foo->han, bar);
    
    if (card_value(&bar) == 11)
    {
        ++foo->soft_cnt;
        foo->ace = 1;
    }
    
    foo->value += card_value(&bar);
    
    if ((foo->value > 21) && (foo->soft_cnt > 0))
    {
        while ((foo->value > 21) && (foo->soft_cnt > 0))
        {
            foo->value -= 10;
            --foo->soft_cnt;
        }
    }
}


/* input: a hand pointer
 * output: none
 * return: a card
 * comments: removes a card from the hand
 */
card hand_deq(hand * foo)
{
    card tmp;
    card_init(&tmp);
    tmp = cardq_deq(&foo->han);
    foo->value -= card_value(&tmp);
    return tmp;
}


/* input: a hand pointer
 * output: none
 * return: none
 * comments: frees the memory used by the hand
 */
void hand_destory(hand  * foo)
{
    cardq_destroy(&foo->han);
}


/* input: a hand pointer
 * output: the hand and it's value
 * return: none
 * comments: prints the hand and its total value with formatting
 */
void hand_print(hand * foo)
{
    int cnt;
    card tmp;

    card_init(&tmp);
    cnt = hand_length(foo);

    while (cnt > 0)
    {
        tmp = cardq_deq(&foo->han);
        card_print(&tmp);
        --cnt;
        cardq_enq(&foo->han, tmp);
    }
       
    fdprintf(OUT, "=");
    
    if (foo->soft_cnt == 1)
        fdprintf(OUT, " soft");
    
    else if (foo->ace == 1)
        fdprintf(OUT, " hard");
    
    fdprintf(OUT, " %d", hand_value(foo));    
}


/* input: a hand pointer
 * output: none
 * return: an int
 * comments: gives the hand's total value
 */
int hand_value(hand * foo)
{
    return foo->value;
}


/* input: a hand pointer
 * output: none
 * return: an int
 * comments: gives the length of the hand
 */
int hand_length(hand * foo)
{
    return cardq_length(&foo->han);
}


/* input: a hand pointer
 * output: none
 * return: an int
 * comments: tells if the hand is empty
 */
int hand_empty(hand * foo)
{
    return cardq_empty(&foo->han);
}


/* input: a hand pointer and an int
 * output: none
 * return: none
 * comments: takes the bet for the hand
 */
void hand_bet(hand * foo, int bar)
{
    foo->bet = bar;
}


/* input: a hand pointer
 * output: none
 * return: an int
 * comments: gives back the bet on the hand
 */
int hand_givebet(hand * foo)
{
    return foo->bet;
}


int hand_bjack(hand * foo)
{
    return foo->bjack;
}

int hand_play(hand * foo, shoe * sho, int hand_num)
{
    card temp1;
    card temp2;

    int x = 0;
    int split = 0;
    int h = 0;
    int d = 0;
    int p = 0;
    char choice = 's';

    if (hand_num == 0)
    {
        temp1 = cardq_deq(&foo->han);
        cardq_enq(&foo->han, temp1);
        temp2 = cardq_deq(&foo->han);
        cardq_enq(&foo->han, temp2);
    }
        
    if (hand_num == 1)
    {
        fdprintf(OUT, "  first hand\n");
        hand_enq(foo, deal_card(sho));
    }

    if (hand_num == 2)
    {
        fdprintf(OUT, "  second hand\n");
        hand_enq(foo, deal_card(sho));
    }

    fdprintf(OUT, "You have : ");
    hand_print(foo);
    fdprintf(OUT, "\n");

    if ((hand_value(foo) == 21) && (hand_length(foo) == 2) &&
            (hand_num == 0))
    {
        split = 3;
        x = 1;
    }

    else
    {
        while (x != 1)
        {
            if (!x)
            {
                if ((hand_value(foo) > 21) && !x)
                {
                    x = 1;
                    foo->value = 0;
                }

                if ((hand_value(foo) == 21) && !x)
                {
                    x = 1;
                    foo->bjack = 1;
                    split = 2;
                }

                else if ((hand_value(foo) < 21) && !x)
                {
                    fdprintf(OUT, "(H)it ");
                    h = 1;
                }
                
                if (!x)
                    fdprintf(OUT, "(S)tand ");
            
                if ((hand_length(foo) <= 2) && !x)
                {
                    fdprintf(OUT, "(D)ouble ");
                    d = 1;
                }
                
                if ((card_face(&temp1) == card_face(&temp2)) && !x
                        && (hand_num == 0) && (hand_length(foo) <= 2))
                {
                    fdprintf(OUT, "s(P)lit ");
                    p = 1;
                }

                if (!x)
                {
                    fdprintf(OUT, "- ");
                    fdscanchar(IN, &choice);
                }
                
                if (strchr(foo->optstr, choice) && !x)
                {
                    if (choice == 's')
                    {
                        x = 1;
                        split = 2;
                    }
                    else if ((choice == 'h') && h)
                    {
                        hand_enq(foo, deal_card(sho));
                        fdprintf(OUT, "You have : ");
                        hand_print(foo);
                        fdprintf(OUT, "\n");
                        if (hand_value(foo) == 21)
                        {
                            split = 2;
                            x = 1;
                        }    
                    }
                    else if ((choice == 'd') && d)
                    {
                        foo->bet = foo->bet * 2;
                        fdprintf(OUT, "  doubled bet to $%d\n", foo->bet);
                        hand_enq(foo, deal_card(sho));
                        fdprintf(OUT, "You have : ");
                        hand_print(foo);
                        fdprintf(OUT, "\n");
                        if (hand_value(foo) <= 21)
                            split = 2;
                        x = 1;
                    }
                    else if ((choice == 'p') && p)
                    {
                        split = 1;
                        x = 1;
                    }
                    else
                        invalid(h, d, p);
                }
                else if (!x)
                    invalid(h, d, p); 
            }/* end if x */
        }/* end while */
    }/* end else */

    return split;
}


void invalid(int h, int d, int p)
{
    fdprintf(OUT, "invalid input! options are > ");
    if (h)
        fdprintf(OUT, "h");
    fdprintf(OUT, "s");
    if (d)
        fdprintf(OUT, "d");
    if (p)
        fdprintf(OUT, "p");
    fdprintf(OUT, "\n");
}

