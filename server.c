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
#include <signal.h>
#include "server.h"
#include "networking.h"

void process( char * s );
void sub_server( int sd, int start );
int run = 1;
static void sighandler(int signo){
  if(signo == SIGINT){//ctrl-c
    int shmidTab = shmget(ftok(".",12), sizeof(char[MAX_CONNECTIONS]), 0);//get the shared memories
    char * pipeTable = (char *)shmat( shmidTab, 0, 0 );
    int shmidNum = shmget(ftok(".",14), sizeof(char[MAX_CONNECTIONS]), 0);
     int shmidEx = shmget(ftok(".",42), sizeof(int), 0);
    int k = 0;
    for( ; k< MAX_CONNECTIONS; k++){//check every pipe
      if( pipeTable[k] == 2){//if it exists and isnt being used, delte
	char path[5];
	sprintf(path, ".%d", k);
	remove(path);
      }else if (! pipeTable[k]){
	printf("\n\n\n\n------\n----please quit all client processes before exting------\n--------\n\n\n\n");
	return;
      }
    }
    shmctl(shmidNum,IPC_RMID,0);
    shmctl(shmidTab,IPC_RMID,0);
   
    exit(1);
  }
}
    
int main() {
  signal(SIGINT, sighandler);
  int shmidNum = shmget(ftok(".",14), sizeof(int), IPC_CREAT | 0644 );
  int *totalConnections = (int *)shmat( shmidNum, 0, 0 );
  int shmidTab = shmget(ftok(".",12), sizeof(char[MAX_CONNECTIONS]), IPC_CREAT | 0644 );
  char * pipeTable = (char *)shmat( shmidTab, 0, 0 );

  printf("+++pipeTable: %p---\n", pipeTable);
  
  set_char_array( PIPE_NC, pipeTable, MAX_CONNECTIONS );
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
    printf("+++fork in main server---\n");
    if ( f == 0 ) {
      
      int er = close(sd);
      error_check(er, "close(sd)");
      
      printf("+++about to run sub_server---\n");
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
  printf("+++[subserver %d] started---\n", connectionNum);
  int shmidEx = shmget(ftok(".",42), sizeof(int), IPC_CREAT | 0644);//used to tell child server that it should aslo exit.
  error_check(shmidEx, "exiting"); 
  int *exiting = (int*) shmat(shmidEx, 0, 0);
  *exiting = 1;

  int f = fork();
  if (f == 0){
    char buffer[MESSAGE_BUFFER_SIZE];
   
    int pipes[MAX_CONNECTIONS];
    set_int_array( 0, pipes, MAX_CONNECTIONS );
    printf("+++npipes cleared---\n");
    
    int shmidNum = shmget(ftok(".",14), sizeof(int), 0);
    int *total = (int *)shmat( shmidNum, 0, 0 );
    error_check(shmidNum, "assigning shmidNum");
    
    int shmidTab = shmget(ftok(".",12), MAX_CONNECTIONS, 0);
    char * pipeTable = (char *)shmat( shmidTab, 0, 0 );

    printf("+++assigned shmem---\n");
    printf("+++pipeTable: %p, \t&pipeTable: %p---\n", pipeTable, &pipeTable);
    
    int o;
    for (o = 0; o < 100; o++)
      printf("pipes[%d] = %d,\t&pipes[%d]: %p\n", o, pipes[o], o, pipes + o);

    for (o = 0; o < 100; o++)
      printf("pipeTable[%d] = %d\n", o, pipeTable[o]);
    
    printf("+++pipeTable: %p---\n", pipeTable);
    
    while (1) {
      printf("+++forever loop---\n");

      read( sd, buffer, sizeof(buffer) );
      //opening the pipes for writing
      open_pipes( pipeTable, total, pipes, connectionNum );
      printf("+++pipes opened---\n");
      if( ! strcmp("EXIT", buffer)){
	printf("+++[client %d] exiting---\n", connectionNum);
	
	int err2 =write(sd, "EXIT" , strlen("EXIT") + 1);//write message to client
	printf("+++sent exit conformation to [client %d]---\n", connectionNum);
	error_check(err2, "writingng bye");

	char path[5];
	sprintf(path, ".%d", connectionNum);
	int rd = open(path, O_WRONLY);
	write(rd, "EXIT",strlen("EXIT") + 1);
	close(rd);
	pipeTable[connectionNum] = PIPE_AFU;//set the pipe in pipetable
	
	close( sd );
	printf("[subserver %d from-client] exiting... \n", connectionNum);
	*total = *total -1;//decremnt total

	open_pipes( pipeTable, total, pipes, connectionNum );
	exit(1);//exit
	
      }
      else { //client did not try to exit
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
    
  }
  
  else{
    char buffer2[MESSAGE_BUFFER_SIZE];
    char buffer3[MESSAGE_BUFFER_SIZE];
    char path[5];
    sprintf(path,".%d",connectionNum);
    int reader = open(path,O_RDONLY);
    while(1){
      printf("+++[subserver %d] listining...---\n", connectionNum);
      read( reader, buffer2, sizeof(buffer2) );

      if (! strcmp(buffer2, "EXIT")) {
	printf("[subserver %d to-client] exiting\n", connectionNum);
	close( reader );
	close( sd );
	exit(0);
      }
      
      printf("+++[subserver %d] recieved <%s>, sent to [client %d]---\n", connectionNum, buffer2, connectionNum);
      write(sd, buffer2, strlen(buffer2) + 1);
    }
  }
  
 
}

void open_pipes( char * pipeTable, int * total, int * pipes, int connectionNum ) {
  printf("+++[open_pipes] pipeTable: %s\ntotal: %d---\nconnectionNum: %d\n", pipeTable, *total, connectionNum);
  int i;
  for(i = 0; i <= *total; i++){
    if( i - connectionNum ) {
      //if pipe is in use && not opened localy
      if ( !pipeTable[i] &&
	   !pipes[i]
	   ) {
	char path[5];
	sprintf(path,".%d", i);
	pipes[i] = open(path,O_WRONLY);
	printf("+++[subserver %d] connecting to [pipe %d]---\n", connectionNum, i);
      }
      //if pipe is not in use and opened locally 
      else if ( pipeTable[i] && 
		pipes[i] ) {
	close( pipes[i] );
	pipes[i] = 0;
	printf("+++[subserver %d] disconnecting from [pipe %d]---\n", connectionNum, i);		
      }
    }
  }
  printf("+++end [open_pipes]---\n");
}

void set_int_array( int value, int array[], int size){
  int i;
  for ( i = 0; i < size; i++)
    array[i]= value;
}

void set_char_array( int value, char array[], int size ){
  int i;
  for ( i = 0; i < size; i++)
    array[i]= value;
}
