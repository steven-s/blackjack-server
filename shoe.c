/* Steven Samson
 * CSCI 1840
 */

#include <stdlib.h>
#include <time.h>
#include "shoe.h"
#include "card.h"

void shuffleCards( card *, int);
void setDeck( card *, int);

/* input: a shoe pointer
 * output: none
 * return: none
 * comments: initializes the shoe
 */
void shoe_init(shoe * foo)
{
    cardq_init(&foo->sho);
}


/* input: a shoe pointer and an int
 * output: none
 * return: none
 * comments: creates the shoe based on the number of decks input, and
 * then shuffles it
 */
void shoe_create(shoe * foo, int decks)
{
    int i;
    card * arr = (card *)malloc((decks * 52) * sizeof(card));
    setDeck(arr, (decks * 52));
    shuffleCards(arr, decks * 52);
    for(i = 0; i < (decks * 52); ++i)
        cardq_enq(&foo->sho, arr[i]);
    cardq_slideset(&foo->sho);
    free(arr);
}


/* input: a shoe pointer
 * output: none
 * return: an int
 * comments: takes a card from the shoe and returns it
 */
card deal_card(shoe * foo)
{
    if (cardq_slidespot(&foo->sho) <= 15)
    {
        shoe_shuffle(foo);
        cardq_slideset(&foo->sho);
    }
    return cardq_deq(&foo->sho);
}


/* input: a shoe pointer
 * output: none
 * return: none
 * comments: shuffles the shoe once it's already in use
 */
void shoe_shuffle(shoe * foo)
{
    int i;
    int size = cardq_length(&foo->sho);
    card * arr = (card *)malloc(size * sizeof(card));
    for(i = 0; i < size; ++i)
        arr[i] = cardq_deq(&foo->sho);
    shuffleCards(arr, size);
    for(i = 0; i < size; ++i)
        cardq_enq(&foo->sho, arr[i]);
    free(arr);
}


/* input: a shoe pointer and a card
 * output: none
 * return: none
 * comments: puts a card back in the shoe
 */
void take_card(shoe * foo, card bar)
{
    cardq_enq(&foo->sho, bar);
}


/* input: a shoe pointer
 * output: none
 * return: none
 * comments: frees the memory used by the shoe
 */
void shoe_destroy(shoe * foo)
{
    cardq_destroy(&foo->sho);
}


/* input: a shoe pointer
 * output: none
 * return: an int
 * comments: gives the number of cards in the shoe
 */
int shoe_size(shoe * foo)
{
    return cardq_length(&foo->sho);
}


/* input: an card pointer and an int
 * output: none
 * return: none
 * comments: shuffles the shoe
 */
void shuffleCards(card * indexArray, int size)
{
    card temp;
    int randElem;
    int i;
    
    srand(time(NULL));

    for(i = 0; i < size; i++)
    {
        randElem = rand() % size;
        temp = indexArray[i];    
        indexArray[i] = indexArray[randElem];
        indexArray[randElem] = temp;
    }
}


/* input: an card pointer, an int
 * output: none
 * return: none
 * comments: creates the decks in the shoe
 */
void setDeck(card * indexArray, int size)
{
    int i;
    card temp;
    card_init(&temp);
    for(i = 0; i < size; ++i)
    {
        card_create(&temp, (i % 13 + 2));
        indexArray[i] = temp;
    }
}

