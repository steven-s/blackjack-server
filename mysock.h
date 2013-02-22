#ifndef MYSOCK_H
#define MYSOCK_H

#define TCP 6
#define QUEUESIZE 10
#define ERROR -1
#define SIZE 256
#define MAX 255


int tcp_server( const int server_port );
int tcp_accept( const int sd );
int tcp_client( const int server_port, const char * host, int * sd );

#endif
