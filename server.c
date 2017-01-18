#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h> 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>                                                             

#include "networking.h"

void process( char * s );
void sub_server( int sd, int start );



int main() {

  int shmidW = shmget(ftok(".",12), sizeof(int[100]), IPC_CREAT | 0644 );
  int shmidR = shmget(ftok(".",13), sizeof(int[100]), IPC_CREAT | 0644 );
  
  int *writeables = (int *)shmat( shmidW, 0, 0 );
  int *readables = (int *)shmat( shmidW, 0, 0 );

  int start = 0;
  
  int sd, connection;

  sd = server_setup();
  
  while (1) {
    connection = server_connect( sd );
    printf("connection from [client %d]\n", start);

    int descriptors[2];
    pipe(descriptors);
    writeables[start]  = descriptors[1];
    readables[start] = descriptors[0];
    start++;
    int f = fork();
    if ( f == 0 ) {

      close(sd);
      sub_server(connection, start - 1);

      int err = shmdt( writeables );
      err = shmdt( readables );
      
      shmctl(shmidW,IPC_RMID,0);
      shmctl(shmidR,IPC_RMID,0);
      exit(0);
    }
    else {
      close( connection );
      
    }
  }

  int err = shmdt( writeables );
  err = shmdt( readables );
  
  shmctl(shmidW,IPC_RMID,0);
  shmctl(shmidR,IPC_RMID,0);
  return 0;
}


void sub_server( int sd, int start ) {
  int shmidW = shmget(ftok(".",12), sizeof(int[100]), IPC_CREAT | 0644 | IPC_EXCL);
  int shmidR = shmget(ftok(".",13), sizeof(int[100]), IPC_CREAT | 0644 | IPC_EXCL);
  
  int *writer = (int *)shmat( shmidW, 0, 0 );
  int *reader = (int *)shmat( shmidR, 0, 0 );


  int f = fork();
  if (f == 0){
    char buffer[MESSAGE_BUFFER_SIZE];
    while (1) {
      read( sd, buffer, sizeof(buffer) );
      printf("[client %d] sent <%s>\n", start, buffer);
      int i;
      for(i = 0; i < start; i++){
	if (i - start){
	  write( writer[i], buffer, sizeof(buffer) );    
	  printf("[subserver %d] sent <%s> to [subserver %d]\n", start, buffer, i);
	}
      }
    }
  }
  
  else{
    char buffer2[MESSAGE_BUFFER_SIZE];
    while(1){
      read( reader[start], buffer2, sizeof(buffer2) );
      printf("[subserver %d] recieved <%s>, sent to [client %d]\n", start, buffer2, start);
      write(sd, buffer2, sizeof(buffer2));
    }
  }

  int err = shmdt( writer );
  err = shmdt( reader );
  
  shmctl(shmidW,IPC_RMID,0);
  shmctl(shmidR,IPC_RMID,0);
}
