#include <stdio.h>

const char *commands[5] = {"help", "clear", "setcolor -t", "setcolor -b", "showinfo"};

// Function to find the length of the commands array
int get_commands_length() {
    return sizeof(commands) / sizeof(commands[0]);
}

int main() {
    int length = get_commands_length();
    printf("Number of commands: %d\n", length);
    return 0;
}
