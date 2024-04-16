#include <stdio.h>
#include <string.h>

#define MAX_COMMANDS 5
char *commands[MAX_COMMANDS] = {"help", "exit", "start", "stop", "restart"};

void printCommands() {
    printf("Available commands:\n");
    for (int i = 0; i < MAX_COMMANDS; i++) {
        printf("%d: %s\n", i + 1, commands[i]);
    }
}

void autocomplete(const char *input) {
    int found = 0;
    for (int i = 0; i < MAX_COMMANDS; i++) {
        if (strncmp(commands[i], input, strlen(input)) == 0) {
            printf("%s\n", commands[i]);
            found = 1;
        }
    }
}

int main() {
    char input[100];
    printf("Enter the beginning of a command, then press Enter: ");
    if (fgets(input, sizeof(input), stdin)) {
        input[strcspn(input, "\n")] = 0; // Remove the newline character
        autocomplete(input);
    }
    return 0;
}
