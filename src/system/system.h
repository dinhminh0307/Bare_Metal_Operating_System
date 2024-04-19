#include "../uart/uart.h"

#define COMMAND_LINE_SIZE 100


typedef struct {
    int key;
    int index;
} string_array_key_value;

extern int currentIndex;

extern const char *commands[5];
extern const char *help[3];
int compare(char *s, char *target);
int getLength(char *s);
int matchCommand(char *s);
int strncmp_custom(const char *s1, const char *s2, int n);
char *strcpy_custom(char *dest, const char *src);
char extract_char(char *str, int index);
int find_char_index(const char *str, char target);
int push(char stack[5][COMMAND_LINE_SIZE], char *element);
int pushNewLine(char *s, int *index);
char *peek(char stack[COMMAND_LINE_SIZE][COMMAND_LINE_SIZE], int index);
char *returnPeek(char stack[COMMAND_LINE_SIZE][COMMAND_LINE_SIZE], int numberOfMinus);
void strcat_custom(char* dest, char* src);
int find_string_index(char *stack[COMMAND_LINE_SIZE], char *target);
char *get_string_by_index(char stack[COMMAND_LINE_SIZE][COMMAND_LINE_SIZE], int index);
int getSizeHelp();