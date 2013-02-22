#ifndef PLAYER_H
#define PLAYER_H

#include "hand.h"
#include "shoe.h"

typedef struct st_player
{
    int cash; /* keeps players cash */
    int value1; /* value of hand 1 */
    int value2; /* value of hand 2 */
    hand one; /* first hand */
    hand two; /* second hand */
}player;

void player_init(player *); /* initializes player */
void alter_cash(player *, int, char); /* changes plaeyr cash */
int player_curcash(player *); /* gives players current cash */
void player_bet(player *, int); /* gets player bet */
int get_bet1(player *); /* gives players bet on hand one */
int get_bet2(player *); /* gives plaeyrs bet on hand two */
int player_value1(player *); /* gives value of hand one */
int player_value2(player *); /* gives value of hand two */
int player_play(player *, shoe *); /* makes player play */
void player_destroy(player *); /* frees memory */
void player_reset(player *, shoe *); /* resets player */

#endif
