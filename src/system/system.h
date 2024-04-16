#define COMMAND_LINE_SIZE 100
extern const char *commands[5];
int compare(char *s, char *target);
int getLength(char *s);
void push(char *s);
int matchCommand(char *s);
int strncmp_custom(const char *s1, const char *s2, int n);
char *strcpy_custom(char *dest, const char *src);