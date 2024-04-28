#include "../system/system.h"
#include "../constant/tag.h"
#include "../constant/color.h"

//Variables declaration
extern volatile int isSetUpSelected;
extern volatile int isWelcomeMsgDisp;
extern char *textColor;
extern char *backGroundColor;

void debugTool();

void printWelcomeMsg(void);
void printMenu();
void printOS(void);
void selectFunction(char *s);
int typeCommand();
void printClearInfor(void);
void printSetColorCommand(void);
void printShowCommand(void);
void clearCommand(void);
int getBoardRevision(void);
int getMacAddress(void);
char *returnTextColor(char *s);
char *returnBackGroundColor(char *s);