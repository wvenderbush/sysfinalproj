#ifndef SERVER_H
#define SERVER_H

#define MESSAGE_BUFFER_SIZE 1000
#define MAX_CONNECTIONS 100

#define PIPE_IU 0
#define PIPE_NC 1
#define PIPE_AFU 2

void open_pipes( char * pipeTable, int * total, int * pipes, int connectionNum );

void set_int_array( int value, int array[], int size );

void set_char_array( int value, char aray[], int size );

#endif
