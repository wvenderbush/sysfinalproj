#ifndef NETWORKING_H
#define NETWORKING_H

#define MESSAGE_BUFFER_SIZE 1000
#define MAX_CONNECTIONS 100
#define PIPE_IU 0
#define PIPE_NC 1
#define PIPE_AFU 2

void error_check( int i, char *s );

int server_setup();
int server_connect(int sd);

int client_connect( char *host );

#endif
