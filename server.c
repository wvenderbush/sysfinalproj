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
  int shmidNum = shmget(ftok(".",14), sizeof(int[100]), IPC_CREAT | 0644 );
  
  int *writeables = (int *)shmat( shmidW, 0, 0 );
  int *readables = (int *)shmat( shmidW, 0, 0 );
  int *totalConnections = (int *)shmat( shmidNum, 0, 0 );

  *totalConnections = 0;
  
  
  int sd, connection;

  sd = server_setup();
  
  while (1) {
    connection = server_connect( sd );
    printf("+++connection from [client %d]---\n", *totalConnections);

    int descriptors[2];
    pipe(descriptors);
    writeables[*totalConnections]  = descriptors[1];
    readables[*totalConnections] = descriptors[0];
    (*totalConnections)++;
    int f = fork();
    if ( f == 0 ) {

      close(sd);
      sub_server(connection, *totalConnections - 1);

      int err = shmdt( writeables );
      err = shmdt( readables );
      err = shmdt( totalConnections );
      
      shmctl(shmidW,IPC_RMID,0);
      shmctl(shmidR,IPC_RMID,0);
      shmctl(shmidNum,IPC_RMID,0);
      exit(0);
    }
    else {
      close( connection );
      
    }
  }

  int err = shmdt( writeables );
  err = shmdt( readables );
  err = shmdt( totalConnections );
  
  shmctl(shmidW,IPC_RMID,0);
  shmctl(shmidR,IPC_RMID,0);
  shmctl(shmidNum,IPC_RMID,0);
  return 0;
}


void sub_server( int sd, int connectionNum ) {
  int shmidW = shmget(ftok(".",12), sizeof(int[100]), 0 );
  int shmidR = shmget(ftok(".",13), sizeof(int[100]), 0 );
  int shmidNum = shmget(ftok(".",14), sizeof(int[100]), 0);
  
  int *writer = (int *)shmat( shmidW, 0, SHM_RDONLY );
  int *reader = (int *)shmat( shmidR, 0, SHM_RDONLY );
  int *total = (int *)shmat( shmidNum, 0, SHM_RDONLY );


  int f = fork();
  if (f == 0){
    char buffer[MESSAGE_BUFFER_SIZE];
    while (1) {
      read( sd, buffer, sizeof(buffer) );
      printf("+++[client %d] sent <%s>---\n", connectionNum, buffer);
      int i;
      printf("+++[subserver %d] thinks there are %d total connections---\n", connectionNum, *total);
      for( i = 0; i < *total; i++){
	if (i - connectionNum) { // if i != connectionNum
	  write( writer[i], buffer, strlen(buffer) );    
	  printf("+++[subserver %d] sent <%s> to [subserver %d]---\n", connectionNum, buffer, i);
	}
      }
    }
  }
  
  else{
    char buffer2[MESSAGE_BUFFER_SIZE];
    while(1){
      read( reader[connectionNum], buffer2, sizeof(buffer2) );
      printf("+++[subserver %d] recieved <%s>, sent to [client %d]---\n", connectionNum, buffer2, connectionNum);
      write(sd, buffer2, strlen(buffer2));
    }
  }
 
}
