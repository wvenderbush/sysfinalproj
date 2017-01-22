#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include "networking.h"
#include "client.h"
#include "markup.c"


#define HEADER "   ______   ________          __\n  / ____/  / ____/ /_  ____ _/ /_\n / /      / /   / __ \\/ __ `/ __/\n/ /___   / /___/ / / / /_/ / /_\n\\____/   \\____/_/ /_/\\__,_/\\__/\n\n"
#define UNDERLINE "----------------------------------\n\n"


int run = 1;
static void sighandler(int signo){
  if (signo == SIGINT){
    printf("signo is SIGINT\n", signo); 
    run = 0;
    fclose(stdin);
  }else{
    printf("signo is %d\n", signo);
  }
}
    

int main( int argc, char *argv[] ) {

  int err;
  signal(SIGINT, sighandler);
  char host[100];
  char user[100];
  printf("\e[1;1H\e[2J");
  printf(HEADER);
  printf(UNDERLINE);
  printf("Enter a unique username:\n\nUsername: ");
  fgets(user, sizeof(user), stdin);
  *strchr(user, '\n') = 0;
  printf("Enter a chatroom address to connect!\n(xxx.xxx.xxx.xxx)\n\nAddress: ");
  fgets(host, sizeof(host), stdin);
  *strchr(host, '\n') = 0;
  
  
   
  int sd;

  sd = client_connect( host );

  char buffer[MESSAGE_BUFFER_SIZE];
  char newbuff[MESSAGE_BUFFER_SIZE];
  int f = fork();
  if (f == 0) {
    while (run) {
      printf("%s: ", user);
      fgets( buffer, sizeof(buffer), stdin );
      strcpy(newbuff, multiParse(buffer));
      printf("\033[1A\x1b[K%s: %s\n", user, newbuff); // deleats prompt and displays formatted message
      char message[MESSAGE_BUFFER_SIZE];
      message[0] = 0; 
      strcat(message, user);
      strcat(message, ": ");
      strcat(message, newbuff);
      if(run){
	err = write( sd, message, sizeof(message) );
	error_check( err, "writing to server");
      }
    }
    printf("[client] received exit signal, sending exit message to server\n");
    char *exiter = "exit\n";
    write(sd,exiter,strlen(exiter));
    printf("exiting...\n");
    
    exit(1);
  }
  else{
    while(run){
      char buffer2[MESSAGE_BUFFER_SIZE];
      err = read ( sd, buffer2, sizeof(buffer2) );
      error_check( err, "reading from server");
      printf("\r %s\n", buffer2);
    }
    exit(1);
      
  }

}
