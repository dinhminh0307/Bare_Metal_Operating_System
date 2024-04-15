#include "../uart/uart.h"

//Variables declaration
extern char *commandLine;

void printWelcomeMsg(char *msg);
void printMenu();
void printOS(void);
void selectFunction();
int typeCommand();
