#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "networking.h"
#include "markup.c"

#define HEADER "   ______   ________          __\n  / ____/  / ____/ /_  ____ _/ /_\n / /      / /   / __ \\/ __ `/ __/\n/ /___   / /___/ / / / /_/ / /_\n\\____/   \\____/_/ /_/\\__,_/\\__/\n\n"
#define UNDERLINE "----------------------------------\n\n"

int main( int argc, char *argv[] ) {

  int err;
  
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
    while (1) {
	printf("%s", user);
  printf(": ");
	fgets( buffer, sizeof(buffer), stdin );
  strcpy(newbuff, multiParse(buffer));
  printf("\033[1A\x1b[K%s: %s\n", user, newbuff);
  char message[MESSAGE_BUFFER_SIZE];
  strcat(message, user);
  strcat(message, ": ");
  strcat(message, newbuff);
	err = write( sd, message, sizeof(message) );
	error_check( err, "writing to server");
    }
  }
  else{
    while(1){
      char buffer2[MESSAGE_BUFFER_SIZE];
      err = read ( sd, buffer2, sizeof(buffer2) );
      error_check( err, "reading from server");
      printf("\r %s\n", buffer2);
    }
  }

  
  return 0;
}
