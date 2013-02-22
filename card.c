/* Steven Samson
 * CSCI 1840
 */

#include "card.h"
#include "fdio.h"

#define OUT 4

/* input: a card pointer
 * output: none
 * return: none
 * comments: initializes the values of a card
 */
void card_init(card * foo)
{
    foo->face = '2';
    foo->value = 0;
}


/* input: a card pointer and an int
 * output: none
 * return: none
 * comments: creates a card from the input integer
 */
void card_create(card * foo, int bar)
{
    if (bar >= 10)
        foo->value = 10;
    if (bar >= 14)
        foo->value = 11;
    if (bar < 10)
        foo->value = bar;
    switch (bar)
    {
        case 2: foo->face = '2'; break;
        case 3: foo->face = '3'; break;
        case 4: foo->face = '4'; break;
        case 5: foo->face = '5'; break;
        case 6: foo->face = '6'; break;
        case 7: foo->face = '7'; break;
        case 8: foo->face = '8'; break;
        case 9: foo->face = '9'; break;
        case 10: foo->face = 'T'; break;
        case 11: foo->face = 'J'; break;
        case 12: foo->face = 'Q'; break;
        case 13: foo->face = 'K'; break;
        case 14: foo->face = 'A'; break;
    }
}


/* input: a card pointer
 * output: the cards face value
 * return: none
 * comments: prints the cards face value
 */
void card_print(card * foo)
{
    char tmp = foo->face;
    fdprintf(OUT, "%c ", tmp);
}


/* input: a card pointer
 * output: none
 * return: an int containing the cards numeric value
 * comments: gives the cards numeric value 
 */
int card_value(card * foo)
{
    return foo->value;
}


/* input: a card pointer
 * output: none
 * return: a char
 * comments: gives the cards face value
 */
char card_face(card * foo)
{
    return foo->face;
}

