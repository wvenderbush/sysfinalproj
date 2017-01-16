#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "networking.h"

void process( char * s );
void sub_server( int sd, int pipe[] );

int main() {

  int sd, connection;

  sd = server_setup();

  int descriptors[2];
  pipe(descriptors);

  while (1) {
   
    connection = server_connect( sd );
    int f = fork();
    if ( f == 0 ) {

      close(sd);
      sub_server(connection, descriptors);

      exit(0);
    }
    else {
      close( connection );
      
    }
  }
  return 0;
}


void sub_server( int sd, int pipe[] ) {
  int f = fork();
  if (f == 0){
    char buffer[MESSAGE_BUFFER_SIZE];
    while (read( sd, buffer, sizeof(buffer) )) {
       write(pipe[1], buffer, sizeof(buffer));    
       printf("sent %s\n", buffer);
    }
  }else{
    char buffer2[MESSAGE_BUFFER_SIZE];
    while(read(pipe[0], buffer2, sizeof(buffer2))){
      printf("recvieed from others: %s\n", buffer2);
      write(sd, buffer2, sizeof(buffer2));
      }
  }
}
