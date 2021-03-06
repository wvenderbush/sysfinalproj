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
#define WELCOME "Welcome to CCHat!\nHere are some helpful CML commands to get you started!\n\n::red:: turns text red\n::blue:: turns text blue\n::magenta:: turns text magenta\n::cyan:: turns text cyan\n::green:: turns text green\n::yellow:: turns text yellow\n::white:: turns text white\n::black:: turns text black\n::basic:: turns text back to the terminal default color\n\n"
#define WELCOME2 "~~smile~~ creates ʘ‿ʘ\n~~shrug~~ creates ¯\\_(ツ)_/¯\n~~scared~~ creates ⊙﹏⊙\n~~disapprove~~ creates ಠ_ಠ\n~~cute~~ creates (｡◕‿◕｡)\n~~excited~~ creates ヽ(*▽*)/\n~~devious~~ creates ಠ‿ಠ\n~~tableflip~~ creates (╯°□°）╯︵ ┻━┻\n~~cat~~ creates ^ᵒᴥᵒ^\n~~fight~~ creates ლ(｀ー´ლ)\n~~bear~~ creates ʕ•ᴥ•ʔ\n~~blob~~ creates ༼ つ ◕_◕ ༽つ\n~~cry~~ creates ಥ_ಥ\n~~love~~ creates (づ￣ ³￣)づ\n~~confused~~ creates (⊙_☉)\n~~fightme~~ creates (ง •̀_•́)ง\n~~hiding~~ creates |_・)\n~~sleep~~ creates (ᴗ˳ᴗ)\n\n(scroll up to view some useful CML commands)\n"

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

int getHeight(){
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w.ws_row;
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

int findDLines(int width, char *message){
  int dLines = 2;
  int length = strlen(message);
  if (length <= width){
    return dLines;
  }
  else{
    while (length > width){
      length = length - width;
      dLines = dLines + 1;
    }
  }
  return dLines;
}   

char * dLineString(int dLines){
  char *ret = (char *) malloc(1000);
  while (dLines != 0){
    strcat(ret, "\033[1A\x1b[K");
    dLines = dLines - 1;
  }
  return ret;
}

void printClear(int height){
  height = height - 10;
  while (height > 0){
    printf("\n");
    height = height - 1;
  }
}

int main( int argc, char *argv[] ) {
  int err;
  signal(SIGINT, sighandler);
  char host[100];
  char rawuser[100];
  printf("\e[1;1H\e[2J");
  printf(HEADER);
  printf("%s\n\n", promptLine(getWidth()));
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
  printf(WELCOME);
  printf(WELCOME2);
  printf(HEADER);
  printf("%s\n", promptLine(getWidth()));
  printClear(getHeight());
  if (f == 0) {
    while (run) {
      printf("%s\n", promptLine(getWidth()));
      fgets( buffer, sizeof(buffer), stdin );
      strcpy(newbuff, multiParse(buffer));
      char message[MESSAGE_BUFFER_SIZE];
      message[0] = 0; 
      strcat(message, user);
      strcat(message, ": ");
      strcat(message, newbuff);
      int dLines = findDLines(getWidth(), newbuff);
      char *dString = dLineString(dLines);
      printf("%s%s: %s", dString, user, newbuff);
      if(run){
	err = write( sd, message, sizeof(message) );
	error_check( err, "writing to server");
      }
    }
    printf("\nYou have been disconnected!\n");
    char *exiter = "EXIT";
    write(sd,exiter,5);
    //printf("writer exiting...\n");
    
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
    //printf("reader exiting... \n");
    exit(1);
      
  }

}
