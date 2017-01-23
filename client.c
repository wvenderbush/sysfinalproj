#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ioctl.h>

#include "networking.h"
#include "client.h"
#include "markup.c"


#define HEADER "   ______   ________          __\n  / ____/  / ____/ /_  ____ _/ /_\n / /      / /   / __ \\/ __ `/ __/\n/ /___   / /___/ / / / /_/ / /_\n\\____/   \\____/_/ /_/\\__,_/\\__/\n\n"
#define UNDERLINE "----------------------------------\n\n"


int run = 1;
static void sighandler(int signo){
  if (signo == SIGINT){
    run = 0;
    fclose(stdin);
  }
}    

int getWidth(){
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w.ws_col;
}

char * promptLine(int width){
  char *ret = (char *) malloc(width + 1);
  int twidth = width;
  while (width != 0){
    strcat(ret, "_");
    width = width - 1;
  }
  ret[twidth + 1] = 0;
  return ret;
}    

int main( int argc, char *argv[] ) {
  int err;
  signal(SIGINT, sighandler);
  char host[100];
  char rawuser[100];
  printf("\e[1;1H\e[2J");
  printf(HEADER);
  printf(UNDERLINE);
  printf("Enter a unique username:\n\nUsername: ");
  fgets(rawuser, sizeof(rawuser), stdin);
  char user[100];
  *strchr(rawuser, '\n') = 0;
  strcpy(user, multiParse(rawuser));
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
      printf("%s\n", promptLine(getWidth()));
      fgets( buffer, sizeof(buffer), stdin );
      strcpy(newbuff, multiParse(buffer));
      printf("\033[1A\033[1A\x1b[K%s: %s", user, newbuff); // deletes prompt and displays formatted message
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
    char *exiter = "EXIT";
    write(sd,exiter,5);
    printf("writer exiting...\n");
    
    exit(1);
  }
  else{
    while(run){
      char buffer2[MESSAGE_BUFFER_SIZE];
      err = read ( sd, buffer2, sizeof(buffer2) );
      error_check( err, "reading from server");
      if( ! strcmp("EXIT", buffer2))
	break;
      printf("\033[1A\x1b[K%s%s\n", buffer2, promptLine(getWidth()));
    }
    printf("reader exiting... \n");
    exit(1);
      
  }

}
