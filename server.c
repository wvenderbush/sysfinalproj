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

  *totalConnections = -1;
    
  int sd, connection;

  sd = server_setup();
  
  while (1) {
    connection = server_connect( sd );
    (*totalConnections)++;

    printf("+++connection from [client %d]---\n", *totalConnections);
    char * path;
    sprintf(path,".%d", *totalConnections);
    int err = mkfifo(path, 0644);
    error_check( err, "making fifo");
    
    int f = fork();
    if ( f == 0 ) {

      close(sd);
      sub_server(connection, *totalConnections);
      int err = shmdt( totalConnections );
      shmctl(shmidNum,IPC_RMID,0);
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

  int f = fork();
  if (f == 0){
    
    char buffer[MESSAGE_BUFFER_SIZE];
    int* fds = (int *)calloc(8,*total);
    int localtotal = *total;
    int j;
    for(j = 0; j < *total; j++){
      if(j - connectionNum){
	char* pipe;
	sprintf(pipe,".%d", j);
	fds[j] = open(pipe,O_WRONLY);
      }
    }
    while (1) {
      if(*total - localtotal){
      for(j =0; j < *total; j++){
	char* pipe;
	sprintf(pipe,".%d", j);
	fds[j] = open(pipe,O_WRONLY);
      }
      localtotal = *total;
    }
      
      read( sd, buffer, sizeof(buffer) );
      printf("+++[client %d] sent <%s>---\n", connectionNum, buffer);
      int i;
      printf("+++[subserver %d] thinks there are %d total connections---\n", connectionNum, *total);
      for( i = 0; i < *total; i++){
	if (i - connectionNum) { // if i != connectionNum
	  write( fds[i], buffer, strlen(buffer) + 1);    
	  printf("+++[subserver %d] sent <%s> to [subserver %d]---\n", connectionNum, buffer, i);
	}
      }
    }
  }
  
  else{
    char buffer2[MESSAGE_BUFFER_SIZE];
    char* name;
    sprintf(name,".%d",connectionNum);
    int reader = open(name,O_RDONLY);
    while(1){
      printf("+++[subserver %d] listining...---\n", connectionNum);
      read( reader, buffer2, sizeof(buffer2) );
      printf("+++[subserver %d] recieved <%s>, sent to [client %d]---\n", connectionNum, buffer2, connectionNum);
      write(sd, buffer2, strlen(buffer2) + 1);
    }
  }
 
}
