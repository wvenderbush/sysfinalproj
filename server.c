#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h> 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>                                                             
#include <sys/stat.h>

#include "server.h"
#include "networking.h"

void process( char * s );
void sub_server( int sd, int start );



int main() {
  int shmidNum = shmget(ftok(".",14), sizeof(int), IPC_CREAT | 0644 );
  int *totalConnections = (int *)shmat( shmidNum, 0, 0 );

  int shmidTab = shmget(ftok(".",12), sizeof(char[MAX_CONNECTIONS]), IPC_CREAT | 0644 );
  char * pipeTable = (char *)shmat( shmidTab, 0, 0 );

  set_array( PIPE_NC, pipeTable, sizeof(char), MAX_CONNECTIONS);
  /*
    int k = 0;
    for ( ; k < MAX_CONNECTIONS; k++)
    pipeTable[k] = PIPE_NC;
  */
  *totalConnections = -1;
    
  int sd, connection;

  sd = server_setup();
  
  while (1) {
    connection = server_connect( sd );

    (*totalConnections)++;
    
    int connectionNum;
    for( connectionNum = 0; ! pipeTable[connectionNum]; connectionNum++ );
    
    if (pipeTable[connectionNum] == PIPE_NC ) {
      char path[5];
      sprintf(path,".%d", connectionNum);
      printf("+++[server] connection from [client %d]---\n", connectionNum);
      printf("+++[server] creating [fifo %d]---\n", connectionNum);

      int err = mkfifo(path, 0644);
      error_check( err, "making fifo");

      pipeTable[ connectionNum ] = PIPE_IU;
    }
    else // == PIPE_AFU
      pipeTable[ connectionNum ] = PIPE_IU;
    
    int f = fork();
    if ( f == 0 ) {

      close(sd);
      sub_server(connection, connectionNum);

      int err = shmdt( totalConnections );
      shmctl(shmidNum,IPC_RMID,0);

      err = shmdt( pipeTable );
      shmctl(shmidTab,IPC_RMID,0);
      exit(0);
    }
    else {
      close( connection );
      
    }
  }

  int err = shmdt( totalConnections );

  shmctl(shmidNum,IPC_RMID,0);
  return 0;
}

void sub_server( int sd, int connectionNum ) {
  int shmidNum = shmget(ftok(".",14), sizeof(int), 0);
  int *total = (int *)shmat( shmidNum, 0, SHM_RDONLY );

  int shmidTab = shmget(ftok(".",12), sizeof(char[MAX_CONNECTIONS]), IPC_CREAT | 0644 );
  char * pipeTable = (char *)shmat( shmidTab, 0, 0 );

  int f = fork();
  if (f == 0){
    
    char buffer[MESSAGE_BUFFER_SIZE];
    int pipes[100];
    set_array( 0, pipes, sizeof( int ), sizeof(pipes) );
    
    int localtotal = *total;
    
    while (1) {

      //opening the pipes for writing
      open_pipes( pipeTable, total, pipes, connectionNum );
      
      read( sd, buffer, sizeof(buffer) );
      printf("+++[client %d] sent <%s>---\n", connectionNum, buffer);
      int i;
      printf("+++[subserver %d] thinks there are %d + 1 total connections---\n", connectionNum, *total);
      for( i = 0; i <= *total; i++){
	if ( i - connectionNum &&
	     pipes[i] &&
	     !pipeTable[i]
	     ) { // if i != connectionNum
	  write( pipes[i], buffer, strlen(buffer) + 1);    
	  printf("+++[subserver %d] sent <%s> to [subserver %d]---\n", connectionNum, buffer, i);
	}
      }
    }
  }
  
  else{
    char buffer2[MESSAGE_BUFFER_SIZE];

    char path[5];
    sprintf(path,".%d",connectionNum);
    int reader = open(path,O_RDONLY);
    
    while(1){
      printf("+++[subserver %d] listining...---\n", connectionNum);
      read( reader, buffer2, sizeof(buffer2) );
      printf("+++[subserver %d] recieved <%s>, sent to [client %d]---\n", connectionNum, buffer2, connectionNum);
      write(sd, buffer2, strlen(buffer2) + 1);
    }
  }
 
}

void open_pipes( char * pipeTable, int * total, int * pipes, int connectionNum ) {
  int j;
  for(j = 0; j <= *total; j++){
    if( j - connectionNum ) {
      //if pipe is in use && not opened localy
      if ( !pipeTable[j] &&
	   !pipes[j]
	   ) {
	char path[5];
	sprintf(path,".%d", j);
	pipes[j] = open(path,O_WRONLY);
	printf("+++[subserver %d] connecting to [pipe %d]---", connectionNum, j);
      }
      //if pipe is not in use and opened locally 
      else if ( pipeTable[j] && 
		pipes[j] ) {
	close( pipes[j] );
	pipes[j] = 0;
	printf("+++[subserver %d] disconnecting from [pipe %d]---", connectionNum, j);		
      }
    }
  }
}

void set_array( int value, void * array, size_t dataSize, int arrayLength ) {
  for ( arrayLength = arrayLength * dataSize; arrayLength; array++, arrayLength-- )
    *( (char *)array ) = value;
}
