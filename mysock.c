/* Steven Samson
 * CSCI 1840
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "mysock.h"

#define TCP 6
#define QUEUESIZE 10

int tcp_server( const int server_port )
{
    int sd;
    struct sockaddr_in sin;
    
    sd = socket(PF_INET, SOCK_STREAM, TCP);
    
    if (-1 == sd)
    {
        printf("socket error\n");
        exit(EXIT_FAILURE);
    }

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(server_port);

    if (-1 == bind(sd, (struct sockaddr *) &sin, sizeof(sin)))
    {
        printf("bind_error\n");
        exit(EXIT_FAILURE);
    }

    if (-1 == listen(sd, QUEUESIZE))
    {
        printf("listen error\n");
        exit(EXIT_FAILURE);
    }

    printf("ready to accept connections\n");
    
    return sd;
}


int tcp_accept( const int sd )
{
    socklen_t addrlen;
    struct sockaddr_in cin;
    
    int sd2 = accept(sd, (struct sockaddr *) &cin, &addrlen);
    
    if (-1 == sd2)
    {
        printf("accept error\n");
        exit(EXIT_FAILURE);
    }

    printf("I have a connection on sd %d\n", sd2);

    return sd2;
}

