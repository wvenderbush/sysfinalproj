#ifndef CLIENT_H
#define CLIENT_H

#define MESSAGE_BUFFER_SIZE 1000

int getWidth();
char * promptLine(int width);
int findDLines(int width, char *message);
char * dLineString(int dLines);
void printClear(int height);

#endif
