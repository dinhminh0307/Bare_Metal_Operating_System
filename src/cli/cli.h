#include "../uart/uart.h"
#include "../system/system.h"

//Variables declaration

void debugTool();

void printWelcomeMsg(char *msg);
void printMenu();
void printOS(void);
void selectFunction(char *s);
int typeCommand();
void printClearInfor(void);
void printSetColorCommand(void);
void printShowCommand(void);
void clearCommand(void);
