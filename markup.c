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
	char *output = (char *) malloc(1024);
	if (strstr(input, "~~smile~~") != NULL){
		char *mark = "~~smile~~";
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
	char *output = (char *) malloc(1024);
	if (strstr(input, "::red::") != NULL){
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
		free(new);
	}
	while (strstr(input, "~~") != 0){ //this is also sorta dangerous
		char *new = emojiParse(input);
		strcpy(input, new);
		free(new);
		} 
	strcat(input, ANSI_COLOR_RESET);
	return input;
}


