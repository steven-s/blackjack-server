/* Steven Samson
 * CSCI 1840
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdarg.h>
#include <unistd.h>

/* input: an int, a character pointer, and variable other arguments
 * output: a formatted version of the input to the indicated file
 * descriptor
 * return: none
 * commments: prints passed arguments to the passed file descriptor
 */
void fdprintf(int fd, char * fmt, ...)
{
    int x;
    va_list ap;
    char buf[256];
    va_start(ap, fmt);
    x = vsnprintf(buf, 255, fmt, ap);
    write(fd, buf, x + 1 );
    va_end(ap);
}


/* input: an int and a pointer to an integer
 * output: none
 * return: none
 * comments: reads in an integer passed by reference from the passed
 * file descriptor
 */
int fdscanint(int fd, int * foo)
{
    int bytesread = 0;
    char buf[256];
    bytesread = read(fd, buf, 255);
    *foo = atoi(buf);
    return bytesread;
}


/* input: an int and a pointer to a character
 * output: none
 * return: none
 * comments: reads in a character passed by reference from the passed
 * file descriptor
 */
int fdscanchar(int fd, char * foo)
{
    int bytesread = 0;
    char buf[256];
    bytesread = read(fd, buf, 255);
    *foo = tolower(buf[0]);
    return bytesread;
}

