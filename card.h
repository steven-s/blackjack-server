/* Steven Samson
 * CSCI 1840
 */

#ifndef CARD_H
#define CARD_H

typedef struct st_card
{
    char face; /* contains cards face value */
    int value; /* contains the cards numeric value */
}card;

void card_init(card *); /* initializes the card */
void card_create(card *, int); /* creates a card */
void card_print(card *); /* prints the card */
int card_value(card *); /* gives the card's value */
char card_face(card *); /* gives cards face */

#endif
