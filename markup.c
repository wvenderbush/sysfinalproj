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

#define SMILEY     "ʘ‿ʘ"
#define SHRUG		"¯\\_(ツ)_/¯"
#define SCARED		"⊙﹏⊙"
#define DISAPPROVE	"ಠ_ಠ"
#define CUTE		"(｡◕‿◕｡)"
#define EXCITED		"ヽ(´▽`)/"
#define DEVIOUS		"ಠ‿ಠ"
#define TABLEFLIP	"(╯°□°）╯︵ ┻━┻"
#define CAT 		"^ᵒᴥᵒ^"
#define FIGHT		"ლ(｀ー´ლ)"
#define BEAR 		"ʕ•ᴥ•ʔ"
#define BLOB 		"༼ つ ◕_◕ ༽つ"
#define CRY 		"ಥ_ಥ"
#define LOVE 		"(づ￣ ³￣)づ"
#define CONFUSED	"(⊙_☉)"
#define FIGHTME		"(ง •̀_•́)ง"
#define HIDING 		"|_・)"
#define SLEEP 		"(ᴗ˳ᴗ)"



char * parse(char *input){
	if (strstr(input, "::red::") != NULL){
		char output[1024];
		char *start = strstr(input, "::red::");
		char *end = start;
		end = end + strlen("::red::");
		start[0] = '\0';
		strcpy(output, input);
		strcat(output, ANSI_COLOR_RED);
		strcat(output, end);
		return output;
	}
	else if (strstr(input, "::green::") != NULL){
		char output[1024];
		char *start = strstr(input, "::green::");
		char *end = start;
		end = end + strlen("::green::");
		start[0] = '\0';
		strcpy(output, input);
		strcat(output, ANSI_COLOR_GREEN);
		strcat(output, end);
		return output;
	}
	else if (strstr(input, "::yellow::") != NULL){
		char output[1024];
		char *start = strstr(input, "::yellow::");
		char *end = start;
		end = end + strlen("::yellow::");
		start[0] = '\0';
		strcpy(output, input);
		strcat(output, ANSI_COLOR_YELLOW);
		strcat(output, end);
		return output;
	}
	else if (strstr(input, "::blue::") != NULL){
		char output[1024];
		char *start = strstr(input, "::blue::");
		char *end = start;
		end = end + strlen("::blue::");
		start[0] = '\0';
		strcpy(output, input);
		strcat(output, ANSI_COLOR_BLUE);
		strcat(output, end);
		return output;
	}
	else if (strstr(input, "::magenta::") != NULL){
		char output[1024];
		char *start = strstr(input, "::magenta::");
		char *end = start;
		end = end + strlen("::magenta::");
		start[0] = '\0';
		strcpy(output, input);
		strcat(output, ANSI_COLOR_MAGENTA);
		strcat(output, end);
		return output;

	}
	else if (strstr(input, "::cyan::") != NULL){
		char output[1024];
		char *start = strstr(input, "::cyan::");
		char *end = start;
		end = end + strlen("::cyan::");
		start[0] = '\0';
		strcpy(output, input);
		strcat(output, ANSI_COLOR_CYAN);
		strcat(output, end);
		return output;

	}
	else if (strstr(input, "::basic::") != NULL){
		char output[1024];
		char *start = strstr(input, "::basic::");
		char *end = start;
		end = end + strlen("::basic::");
		start[0] = '\0';
		strcpy(output, input);
		strcat(output, ANSI_COLOR_RESET);
		strcat(output, end);
		return output;
	}
	return input;
}

char * multiparse(char *input){
	while (strstr(input, "::") != 0){ //this is a dangerous base case
		char *new = parse(input);
		strcpy(input, new);
	}
	strcat(input, ANSI_COLOR_RESET);
	return input;
}

int main(int argc, char const *argv[]) {

  // printf(ANSI_COLOR_RED     "This text is RED!"     ANSI_COLOR_RESET "\n");
  // printf(ANSI_COLOR_GREEN   "This text is GREEN!"   ANSI_COLOR_RESET "\n");
  // printf(ANSI_COLOR_YELLOW  "This text is YELLOW!"  ANSI_COLOR_RESET "\n");
  // printf(ANSI_COLOR_BLUE    "This text is BLUE!"    ANSI_COLOR_RESET "\n");
  // printf(ANSI_COLOR_MAGENTA "This text is MAGENTA!" ANSI_COLOR_RESET "\n");
  // printf(ANSI_COLOR_CYAN    "This text is CYAN!"    ANSI_COLOR_RESET "\n\n\n");

  char test[] = "This ::red::text ::basic::is ::red::red ::yellow::and ::magenta::this is ::cyan::blue";

  printf("%s\n", multiparse(test));
  // printf("%s\n", SMILEY);
  // printf("%s\n", SHRUG);

  return 0;
}