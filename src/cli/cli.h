#include "../uart/uart.h"
#include "../system/system.h"
#define COMMAND_LINE_SIZE 100
//Variables declaration

void debugTool();

void printWelcomeMsg(char *msg);
void printMenu();
void printOS(void);
void selectFunction(char *s);
int typeCommand();
