#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "networking.h"

void process( char * s );
void sub_server( int sd, int start );

int writeables[100];
int readables[100];
int start = 0;

int main() {

  int sd, connection;

  sd = server_setup();
  
  while (1) {
    connection = server_connect( sd );
    int descriptors[2];
    pipe(descriptors);
    writeables[start]  = descriptors[1];
    readables[start] = descriptors[0];
    start++;
    printf("%d\n", start);
    int f = fork();
    if ( f == 0 ) {

      close(sd);
      sub_server(connection, start -1);

      exit(0);
    }
    else {
      close( connection );
      
    }
  }
  return 0;
}


void sub_server( int sd, int start ) {
  int f = fork();
  if (f == 0){
    char buffer[MESSAGE_BUFFER_SIZE];
    while (read( sd, buffer, sizeof(buffer) )) {
      int *writer;
      writer = writeables; 
      int i;
      for(i = 0; i < start; i++){
	write(writer[i], buffer, sizeof(buffer));    
	printf("sent %s\n", buffer);
      }
    }
  }else{
    char buffer2[MESSAGE_BUFFER_SIZE];
    while(read(readables[start], buffer2, sizeof(buffer2))){
      printf("recvieed from others: %s\n", buffer2);
      write(sd, buffer2, sizeof(buffer2));
    }
  }
}
