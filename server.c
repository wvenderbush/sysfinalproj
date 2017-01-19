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
#include "networking.h"

void process( char * s );
void sub_server( int sd, int start );



int main() {
  int shmidNum = shmget(ftok(".",14), sizeof(int), IPC_CREAT | 0644 );
  int *totalConnections = (int *)shmat( shmidNum, 0, 0 );

  int shmidTab = shmget(ftok(".",12), sizeof(char[MAX_CONNECTIONS]), IPC_CREAT | 0644 );
  char * pipeTable = (char *)shmat( shmidTab, 0, 0 );

  int k = 0;
  for ( ; k < MAX_CONNECTIONS; k++)
    pipeTable[k] = PIPE_NC
  
  *totalConnections = -1;
    
  int sd, connection;

  sd = server_setup();
  
  while (1) {
    connection = server_connect( sd );
    (*totalConnections)++;
    printf("+++connection from [client %d]---\n", *totalConnections);
    
    int connectionNum;
    for( connectionNum = 0; ! pipeTable[connectionNum]; connectionNum++ );
    
    if (pipeTable[connectionNum] == 1) {
      char path[5];
      sprintf(path,".%d", connectionNum);
      printf("creating [fifo %d]", connectionNum);

      int err = mkfifo(path, 0644);
      error_check( err, "making fifo");

      pipeTable[ connectionNum ] = 0;
    }
    else
      pipeTable[ connectionNum ] = 0;
    
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
    
    int localtotal = *total;
    
    
    while (1) {

      int j;
      for(j = 0; j <= *total; j++){
	if(j - connectionNum && !pipeTable[j] ){
	  char path[5];
	  sprintf(path,".%d", j);
	  pipes[j] = open(path,O_WRONLY);
	}
      }
      
      read( sd, buffer, sizeof(buffer) );
      printf("+++[client %d] sent <%s>---\n", connectionNum, buffer);
      int i;
      printf("+++[subserver %d] thinks there are %d + 1 total connections---\n", connectionNum, *total);
      for( i = 0; i <= *total; i++){
	if (i - connectionNum) { // if i != connectionNum
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
