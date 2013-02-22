/* Steven Samson
 * CSCI 1840
 */

#include <stdio.h>
#include <stdlib.h>


#include "dealer.h"
#include "player.h"
#include "shoe.h"
#include "card.h"
#include "hand.h"
#include "fdio.h"
#include "mysock.h"


/* prototypes */
int play_insure(player *, dealer *, int);
void play_game(player *, shoe *, dealer *);


/* macros for the file descriptor numbers to make changes easy */
#define OUT 4
#define IN 4

#define MYPORT 16900

int main()
{
    /* variables used throughout the program */
    int money = 0;
    int decks = 0;
    
    shoe shoe1; /* shoe */
    player player1; /* player */
    dealer dealer1; /* dealer */

    int sd = tcp_server(MYPORT);
    tcp_accept(sd);

    /* gets  the players initial cash */
    fdprintf(OUT, "\nStarting money - ");
    fdscanint(IN, &money);
    
    /* gets the number of decks in the shoe */
    fdprintf(OUT, "Number of decks in the shoe - ");
    fdscanint(IN, &decks);
    
    fdprintf(OUT, "  starting game\n");

    /* initializes the player, shoe, and dealer */
    shoe_init(&shoe1);
    player_init(&player1);
    dealer_init(&dealer1);
    
    alter_cash(&player1, money, '+'); /* gives the player their cash */
    
    fdprintf(OUT, "  shuffling decks\n");

    shoe_create(&shoe1, decks); /* creates and shuffles the shoe */
          
    play_game(&player1, &shoe1, &dealer1); /* plays the game */

    /* frees the memory used by the structures */
    shoe_destroy(&shoe1);
    player_destroy(&player1);
    dealer_destroy(&dealer1);

    printf("connection closed\n");
   
    return 0;
}



void play_game(player * play, shoe * sho, dealer * deal)
{

    int x = 0;
    int bet = 0;
    int winning = 0;

    int money = player_curcash(play);

    /* plays the game until 0 is entered for the bet */
    while (x != 1)
    {
        if (player_curcash(play) > 0)
        {
            fdprintf(OUT, "Place bet (%d available, 0 ends the game ) - ", 
                    player_curcash(play));
            fdscanint(IN, &bet);
        }
        if (player_curcash(play) <= 0)
        {
            fdprintf(OUT, "You're out of money!\n\n");
            x = 1;
        }

        if ((bet > 0) && !(bet > player_curcash(play)) &&
                (player_curcash(play) > 0))
        {
            int insure = 0;
            int test = 0;
            int bust = 0;
            
            insure = dealer_start(deal, sho);

            if (insure == 11)
            {
                test = play_insure(play, deal, bet);
            }
            if (!test)
            {
                player_bet(play, bet);
                bust = player_play(play, sho);
                if (bust)
                {
                    int deal_bjack;
                    
                    if (!(bust == 3))
                        deal_bjack = dealer_play(deal, sho);
                    
                    if ((bust == 1) && (!deal_bjack))/* no split */
                    {
                        int d_total = dealer_value(deal);
                        int p_total = player_value1(play);
                        
                        if (p_total < d_total)
                        {
                            alter_cash(play, get_bet1(play), '-');
                            fdprintf(OUT, "Dealer wins\n\n");
                        }
                        
                        if (p_total > d_total)
                        {
                            alter_cash(play, get_bet1(play), '+');
                            fdprintf(OUT, "You win $%d\n\n",
                                    get_bet1(play));
                        }
                        
                        if (p_total == d_total)
                            fdprintf(OUT, "push\n\n");
                    }
                    if ((bust == 2) && (!deal_bjack)) /* split */
                    {
                        int d_total = dealer_value(deal);
                        int p_total1 = player_value1(play);
                        int p_total2 = player_value2(play);
                        
                        fdprintf(OUT, "first hand - ");

                        if (p_total1 < d_total)
                        {
                            alter_cash(play, get_bet1(play), '-');
                            fdprintf(OUT, "Dealer wins\n");
                        }
                        if (p_total1 > d_total)
                        {
                            alter_cash(play, get_bet1(play), '+');
                            fdprintf(OUT, "You win $%d\n",
                                    get_bet1(play));
                        }
                        if (p_total1 == d_total)
                            fdprintf(OUT, "push\n");

                        fdprintf(OUT, "second hand - ");

                        if (p_total2 < d_total)
                        {
                            alter_cash(play, get_bet2(play), '-');
                            fdprintf(OUT, "Dealer wins\n");
                        }
                        if (p_total2 > d_total)
                        {
                            alter_cash(play, get_bet2(play), '+');
                            fdprintf(OUT, "You win $%d",
                                    get_bet2(play));
                        }
                        if (p_total2 == d_total)
                            fdprintf(OUT, "push\n");

                        fdprintf(OUT, "\n");
                    }
                    if (bust == 3)
                    {
                        int win = 3 * get_bet1(play) / 2;
                        alter_cash(play, win, '+');
                        fdprintf(OUT, "BLACKJACK!!!\nYou win $%d\n\n", win);
                    }
                }
                if (bust == 0)
                {
                    fdprintf(OUT, "Busted!\n\n");
                    alter_cash(play, get_bet1(play), '-');
                }
            }/* end if !test */
            player_reset(play, sho);
            dealer_reset(deal, sho);
        }/* end if bet > 0 */

        if (bet <= 0)
        {
            x = 1;
        }

        if (bet > player_curcash(play))
        {
            fdprintf(OUT, "You can't bet more than you have\n");
        }
    }/* end while */
    
    winning = player_curcash(play) - money;
    if (winning > 0)
        fdprintf(OUT, "You have won $%d\n\n", winning);
    if (winning == 0)
        fdprintf(OUT, "You broke even\n\n");
    if (winning < 0)
        fdprintf(OUT, "You lost $%d\n\n", money - player_curcash(play));
}


int play_insure(player * play, dealer * deal, int bet)
{
    char yn = 'n';
    int win = 0;
    
    fdprintf(OUT, "Do you wish to take insurance for $%d (y/n) - ",
                bet / 2);
    fdscanchar(IN, &yn);

    if (yn == 'y')
    {
        if (dealer_value(deal) == 21)
        {
            fdprintf(OUT, "Dealer has 21, you win!\n");
            alter_cash(play, bet / 2, '+');
            win = 1;
        }
        else
        {
            fdprintf(OUT, "Dealer does not have 21, insurance lost\n");
            alter_cash(play, bet / 2, '-');
        }
    }

    return win;
}

