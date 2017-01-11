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

char * multitok(char *input, char *delimiter){
    static char *string;
    if (input != NULL)
        string = input;

    if (string == NULL)
        return string;

    char *end = strstr(string, delimiter);
    if (end == NULL) {
        char *temp = string;
        string = NULL;
        return temp;
    }

    char *temp = string;

    *end = '\0';
    string = end + strlen(delimiter);
    return temp;
}


char * parse(char *input){ //multiple tags in one line (ie. 2 ::red:: breaks the code because of multitok)
	if (strstr(input, "::red::") != NULL){
		char output[1024];
		char *start = multitok(input, "::red::");
		char *end = multitok(NULL, "::red::");
		strcpy(output, start);
		strcat(output, ANSI_COLOR_RED);
		strcat(output, end);
		strcat(output, ANSI_COLOR_RESET);
		return output;
	}
	else if (strstr(input, "::green::") != NULL){
		char output[1024];
		char *start = multitok(input, "::green::");
		char *end = multitok(NULL, "::green::");
		strcpy(output, start);
		strcat(output, ANSI_COLOR_GREEN);
		strcat(output, end);
		strcat(output, ANSI_COLOR_RESET);
		return output;
	}
	else if (strstr(input, "::yellow::") != NULL){
		char output[1024];
		char *start = multitok(input, "::yellow::");
		char *end = multitok(NULL, "::yellow::");
		strcpy(output, start);
		strcat(output, ANSI_COLOR_YELLOW);
		strcat(output, end);
		strcat(output, ANSI_COLOR_RESET);
		return output;
	}
	else if (strstr(input, "::blue::") != NULL){
		char output[1024];
		char *start = multitok(input, "::blue::");
		char *end = multitok(NULL, "::blue::");
		strcpy(output, start);
		strcat(output, ANSI_COLOR_BLUE);
		strcat(output, end);
		strcat(output, ANSI_COLOR_RESET);
		return output;
	}
	else if (strstr(input, "::magenta::") != NULL){
		char output[1024];
		char *start = multitok(input, "::magenta::");
		char *end = multitok(NULL, "::magenta::");
		strcpy(output, start);
		strcat(output, ANSI_COLOR_MAGENTA);
		strcat(output, end);
		strcat(output, ANSI_COLOR_RESET);
		return output;

	}
	else if (strstr(input, "::cyan::") != NULL){
		char output[1024];
		char *start = multitok(input, "::cyan::");
		char *end = multitok(NULL, "::cyan::");
		strcpy(output, start);
		strcat(output, ANSI_COLOR_CYAN);
		strcat(output, end);
		strcat(output, ANSI_COLOR_RESET);
		return output;

	}
	else if (strstr(input, "::basic::") != NULL){
		char output[1024];
		char *start = multitok(input, "::basic::");
		char *end = multitok(NULL, "::basic::");
		strcpy(output, start);
		strcat(output, ANSI_COLOR_RESET);
		strcat(output, end);
		strcat(output, ANSI_COLOR_RESET);
		return output;
	}
	return input;
}

char * multiparse(char *input){
	while (strstr(input, "::") != 0){ //this is a dangerous base case
		char *new = parse(input);
		strcpy(input, new);
	}
	return input;
}

int main(int argc, char const *argv[]) {

  printf(ANSI_COLOR_RED     "This text is RED!"     ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_GREEN   "This text is GREEN!"   ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_YELLOW  "This text is YELLOW!"  ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_BLUE    "This text is BLUE!"    ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_MAGENTA "This text is MAGENTA!" ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_CYAN    "This text is CYAN!"    ANSI_COLOR_RESET "\n\n\n");

  char test[] = "This text is ::red::red ::green::and ::magenta::this is ::cyan::blue";

  printf("%s\n", multiparse(test));

  return 0;
}