#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "markup.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

char * parse(char *input){
	if (strstr(input, "::red::") != NULL){
		char *output = strcat(ANSI_COLOR_RED, input);
		output = strcat(input, ANSI_COLOR_RESET);
		return output;
	}
	else if (strstr(input, "::green::") != NULL){

	}
	else if (strstr(input, "::yellow::") != NULL){

	}
	else if (strstr(input, "::blue::") != NULL){

	}
	else if (strstr(input, "::magenta::") != NULL){

	}
	else if (strstr(input, "::cyan::") != NULL){

	}





}

int main(int argc, char const *argv[]) {

  printf(ANSI_COLOR_RED     "This text is RED!"     ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_GREEN   "This text is GREEN!"   ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_YELLOW  "This text is YELLOW!"  ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_BLUE    "This text is BLUE!"    ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_MAGENTA "This text is MAGENTA!" ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_CYAN    "This text is CYAN!"    ANSI_COLOR_RESET "\n\n\n");

  char test[] = "::red::testing";

  printf(parse(test));

  return 0;
}