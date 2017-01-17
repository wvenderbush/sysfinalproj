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

#define SMILE       "ʘ‿ʘ"
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


char * emojiParse(char *input){
	if (strstr(input, "~~smile~~") != NULL){
		char *mark = "~~smile~~";
		char output[1024];
		char *start = strstr(input, mark);
		char *end = start;
		end = end + strlen(mark);
		start[0] = '\0';
		strcpy(output, input);
		strcat(output, SMILE);
		strcat(output, end);
		return output;
	}
	if (strstr(input, "~~shrug~~") != NULL){
		char *mark = "~~shrug~~";
		char output[1024];
		char *start = strstr(input, mark);
		char *end = start;
		end = end + strlen(mark);
		start[0] = '\0';
		strcpy(output, input);
		strcat(output, SHRUG);
		strcat(output, end);
		return output;
	}
	if (strstr(input, "~~scared~~") != NULL){
		char *mark = "~~scared~~";
		char output[1024];
		char *start = strstr(input, mark);
		char *end = start;
		end = end + strlen(mark);
		start[0] = '\0';
		strcpy(output, input);
		strcat(output, SCARED);
		strcat(output, end);
		return output;
	}
	if (strstr(input, "~~disapprove~~") != NULL){
		char *mark = "~~disapprove~~";
		char output[1024];
		char *start = strstr(input, mark);
		char *end = start;
		end = end + strlen(mark);
		start[0] = '\0';
		strcpy(output, input);
		strcat(output, DISAPPROVE);
		strcat(output, end);
		return output;
	}
	if (strstr(input, "~~cute~~") != NULL){
		char *mark = "~~cute~~";
		char output[1024];
		char *start = strstr(input, mark);
		char *end = start;
		end = end + strlen(mark);
		start[0] = '\0';
		strcpy(output, input);
		strcat(output, CUTE);
		strcat(output, end);
		return output;
	}
	if (strstr(input, "~~excited~~") != NULL){
		char *mark = "~~excited~~";
		char output[1024];
		char *start = strstr(input, mark);
		char *end = start;
		end = end + strlen(mark);
		start[0] = '\0';
		strcpy(output, input);
		strcat(output, EXCITED);
		strcat(output, end);
		return output;
	}
	if (strstr(input, "~~devious~~") != NULL){
		char *mark = "~~devious~~";
		char output[1024];
		char *start = strstr(input, mark);
		char *end = start;
		end = end + strlen(mark);
		start[0] = '\0';
		strcpy(output, input);
		strcat(output, DEVIOUS);
		strcat(output, end);
		return output;
	}
	if (strstr(input, "~~tableflip~~") != NULL){
		char *mark = "~~tableflip~~";
		char output[1024];
		char *start = strstr(input, mark);
		char *end = start;
		end = end + strlen(mark);
		start[0] = '\0';
		strcpy(output, input);
		strcat(output, TABLEFLIP);
		strcat(output, end);
		return output;
	}
	if (strstr(input, "~~cat~~") != NULL){
		char *mark = "~~cat~~";
		char output[1024];
		char *start = strstr(input, mark);
		char *end = start;
		end = end + strlen(mark);
		start[0] = '\0';
		strcpy(output, input);
		strcat(output, CAT);
		strcat(output, end);
		return output;
	}
	if (strstr(input, "~~fight~~") != NULL){
		char *mark = "~~fight~~";
		char output[1024];
		char *start = strstr(input, mark);
		char *end = start;
		end = end + strlen(mark);
		start[0] = '\0';
		strcpy(output, input);
		strcat(output, FIGHT);
		strcat(output, end);
		return output;
	}
	if (strstr(input, "~~bear~~") != NULL){
		char *mark = "~~bear~~";
		char output[1024];
		char *start = strstr(input, mark);
		char *end = start;
		end = end + strlen(mark);
		start[0] = '\0';
		strcpy(output, input);
		strcat(output, BEAR);
		strcat(output, end);
		return output;
	}
	if (strstr(input, "~~blob~~") != NULL){
		char *mark = "~~blob~~";
		char output[1024];
		char *start = strstr(input, mark);
		char *end = start;
		end = end + strlen(mark);
		start[0] = '\0';
		strcpy(output, input);
		strcat(output, BLOB);
		strcat(output, end);
		return output;
	}
	if (strstr(input, "~~cry~~") != NULL){
		char *mark = "~~cry~~";
		char output[1024];
		char *start = strstr(input, mark);
		char *end = start;
		end = end + strlen(mark);
		start[0] = '\0';
		strcpy(output, input);
		strcat(output, CRY);
		strcat(output, end);
		return output;
	}
	if (strstr(input, "~~love~~") != NULL){
		char *mark = "~~love~~";
		char output[1024];
		char *start = strstr(input, mark);
		char *end = start;
		end = end + strlen(mark);
		start[0] = '\0';
		strcpy(output, input);
		strcat(output, LOVE);
		strcat(output, end);
		return output;
	}
	if (strstr(input, "~~confused~~") != NULL){
		char *mark = "~~confused~~";
		char output[1024];
		char *start = strstr(input, mark);
		char *end = start;
		end = end + strlen(mark);
		start[0] = '\0';
		strcpy(output, input);
		strcat(output, CONFUSED);
		strcat(output, end);
		return output;
	}
	if (strstr(input, "~~fightme~~") != NULL){
		char *mark = "~~fightme~~";
		char output[1024];
		char *start = strstr(input, mark);
		char *end = start;
		end = end + strlen(mark);
		start[0] = '\0';
		strcpy(output, input);
		strcat(output, FIGHTME);
		strcat(output, end);
		return output;
	}
	if (strstr(input, "~~hiding~~") != NULL){
		char *mark = "~~hiding~~";
		char output[1024];
		char *start = strstr(input, mark);
		char *end = start;
		end = end + strlen(mark);
		start[0] = '\0';
		strcpy(output, input);
		strcat(output, HIDING);
		strcat(output, end);
		return output;
	}
	if (strstr(input, "~~sleeping~~") != NULL){
		char *mark = "~~sleeping~~";
		char output[1024];
		char *start = strstr(input, mark);
		char *end = start;
		end = end + strlen(mark);
		start[0] = '\0';
		strcpy(output, input);
		strcat(output, SLEEP);
		strcat(output, end);
		return output;
	}

	return input;
}



char * colorParse(char *input){
	// char *mark = strstr(input, "::");
	// if (mark == NULL){
	// 	return input;
	// }
	// else {
	// 	mark = mark + 2;
	// 	if (strstr(mark, "::") == NULL){
	// 		return NULL;
	// 	}
	// 	char tag[100];
	// 	tag[0] = ':';
	// 	tag[1] = ':';
	// 	int counter = 2;
	// 	//while (strcmp(strcat(mark[0], mark[1]), "::")){
	// 	while (strcmp(mark[0], ':') != 0){
	// 		tag[counter] = mark[0];
	// 		mark = mark + 1;
	// 		counter = counter + 1;
	// 	}
	// 	printf("%s\n", tag);
	// 	printf("%s\n", mark);
	// }
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

char * multiParse(char *input){
	while (strstr(input, "::") != 0){ //this is a dangerous base case
		char *new = colorParse(input);
		strcpy(input, new);
	}
	while (strstr(input, "~~") != 0){ //this is also sorta dangerous
		char *new = emojiParse(input);
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

  char test[] = "I am this guy: ::red::~~smile~~ ::basic::yes I am a ::yellow::~~fightme~~::basic::!";

  printf("%s\n", multiParse(test));
  // printf("%s\n", SMILEY);
  // printf("%s\n", SHRUG);

  return 0;
}

