#include <string.h>
#include <stdio.h>

#define MAX_ELEMENTS 100
#define MAX_LENGTH 50

int getLength(char stack[MAX_ELEMENTS][MAX_LENGTH]) {
    int count = 0;
    for (int i = 0; i < MAX_ELEMENTS; i++) {
        if (stack[i][0] != '\0') { // assuming empty strings are marked by a null terminator at the start
            count++;
        } else {
            break;
        }
    }
    return count;
}


// Function to push a string onto the stack
int push(char stack[MAX_ELEMENTS][MAX_LENGTH], char *element) {
    if (element == NULL || element[0] == '\0') return 0; // Element must not be an empty string

    int length = getLength(stack);
    if (length >= MAX_ELEMENTS) return 0; // Check for stack overflow

    // Add the new element to the stack
    strncpy(stack[length], element, MAX_LENGTH);
    stack[length][MAX_LENGTH - 1] = '\0'; // Ensure null termination

    return 1; // Return success
}

int main() {
    char commands[MAX_ELEMENTS][MAX_LENGTH] = {0}; // Initialize stack with empty strings

    // Test the push function
    char s[] = "Hello";
    push(commands, s);

    char t[] = "World";
    push(commands, t);
    
    printf("%s", commands[1]);
    return 0;
}
