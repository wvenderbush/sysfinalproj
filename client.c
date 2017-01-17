#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "networking.h"

#define HEADER "   ______   ________          __\n  / ____/  / ____/ /_  ____ _/ /_\n / /      / /   / __ \\/ __ `/ __/\n/ /___   / /___/ / / / /_/ / /_\n\\____/   \\____/_/ /_/\\__,_/\\__/\n\n"
#define UNDERLINE "----------------------------------\n\n"

int main( int argc, char *argv[] ) {

  char host[100];
  printf("\e[1;1H\e[2J");
  printf(HEADER);
  printf(UNDERLINE);
  printf("Enter a host to connect (format xxx.xxx.xxx.xxx)\n>");
  fgets(host, sizeof(host), stdin);
  *strchr(host, '\n') = 0;
  
  
   
  int sd;

  sd = client_connect( host );

  char buffer[MESSAGE_BUFFER_SIZE];
  int f = fork();
  if (f == 0) {
    printf("%d", f);
      while (1) {
	printf("enter message: ");
	fgets( buffer, sizeof(buffer), stdin );
	char *p = strchr(buffer, '\n');
	write( sd, buffer, sizeof(buffer) );
	
      }
  }
  else{
    printf("%d", f);
    while(1){
      char buffer2[MESSAGE_BUFFER_SIZE];
      read ( sd, buffer2, sizeof(buffer2) );
      printf("ip sent this: %s\n", buffer2);
    }
  }

  
  return 0;
}
