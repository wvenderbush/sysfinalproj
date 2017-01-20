#ifndef NETWORKING_H
#define NETWORKING_H

void error_check( int i, char *s );

int server_setup();
int server_connect(int sd);

int client_connect( char *host );

#endif
