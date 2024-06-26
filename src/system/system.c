#include "./system.h"
const char *commands[5] = {"help", "clear", "setcolor", "showinfo", "boot"};
const char *help[4] = {"help clear", "help setcolor", "help showinfo", "help boot"};
const char *setcolor[2] = {"setcolor -t", "setcolor -b"};

#define HELP_SIZE sizeof(help) / sizeof(help[0])
int numberCommands[5];
int currentIndex = 0;
int getLength(char *s) {
    int ctr = 0;
    if(*s == '\0') {
        return 0;
    }
    while (*s != '\0') {
        ctr++;
        s++;
    }
    return ctr;
}

char *strcpy_custom(char *dest, const char *src) {
     while (*src) {          
        *dest = *src;       
        dest++;             
        src++;             
    }
    *dest = '\0';           
}

int strncmp_custom(const char *s1, const char *s2, int n) {
    if (n == 0) return 0;  // If n is zero, no characters are compared, and the function returns 0.

    while (n-- > 1 && *s1 && *s1 == *s2) { // decrease n and compare s1 and s2
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}



int compare(char *s, char *target) {
    while (*s && *s == *target) {
        s++;
        target++;
    }
    // If both strings ended, they match, otherwise they don't
    return *s == '\0' && *target == '\0';
}

int matchCommand(char *s) {
    if(compare(s, "help\n")) {
        return 1;
    } else if(compare(s, "help clear\n")) {
        return 2;
    } else if(compare(s, "help setcolor\n")) {
        return 3;
    } else if(compare(s, "help showinfo\n")) {
        return 4;
    } else if(compare(s, "clear\n")) {
        return 5;
    } else if(compare(s, "showinfo\n")) {
        return 6;
    } else if(compare(s, "boot\n")) {
        return 9;
    } else if(compare(s, "help boot\n")) {
        return 10;
    }

    if(strncmp_custom(s, "setcolor -t ", 12) == 0) {
        return 7;
    } else if(strncmp_custom(s, "setcolor -b ", 12) == 0) {
        return 8;
    }
    return 0;
}

int stringToInt(const char *str) {
    int result = 0;       
    int sign = 1;         

    // Check if there is a minus sign at the beginning of the string
    if (*str == '-') {
        sign = -1;
        str++;            
    }

   
    while (*str != '\0') {
        
        if (*str >= '0' && *str <= '9') {
            result = result * 10 + (*str - '0');  
        } else {
            // If the character is not a digit, return 0 or handle the error appropriately
            return 0;
        }
        str++; 
    }

    return result * sign; 
}

char extract_char(char *str, int index) {
    if (getLength(str) == 0) {
        return '\0';  
    }

    for (int i = 0; str[i] != '\0'; i++) {
        if (i == index) {
            str[i] = '\0';
        }
    }
    return '\0';  
}

int find_char_index(const char *str, char target) {
    if (getLength(str) == 0) {
        return -1;  
    }

    int index = 0; 
    while (str[index] != '\0') {  // Loop until the end of the string
        if (str[index] == target) {
            return index;  // Return the current index if target is found
        }
        index++;  
    }
    return -1;  
}

int get2dArrayLength(char stack[COMMAND_LINE_SIZE][COMMAND_LINE_SIZE]) {
    int count = 0;
    for (int i = 0; i < COMMAND_LINE_SIZE; i++) {
        if (stack[i][0] != '\0') { // assuming empty strings are marked by a null terminator at the start
            count++;
        } else {
            break;
        }
    }
    return count;
}


int push(char stack[COMMAND_LINE_SIZE][COMMAND_LINE_SIZE], char *element) {
    if (getLength(element) == 0 || *element == '\0') return 0; // Element must not be an empty string

    int length = get2dArrayLength(stack);
    if (length >= COMMAND_LINE_SIZE) { 
        return 0; // Check for stack overflow
    } 

    // Add the new element to the stack
    strcpy_custom(stack[length], element);
    stack[length][COMMAND_LINE_SIZE - 1] = '\0'; // Ensure null termination

    return 1; 
}

int pushNewLine(char *s, int *index) {
    int ctr = 0;
    while (*s != '\0') {
        s++;
    }
    *s = '\n';
}

char *peek(char stack[COMMAND_LINE_SIZE][COMMAND_LINE_SIZE], int index) {
    int length = get2dArrayLength(stack);
    if(index > length) {
        return stack[0];
    }
    if(get2dArrayLength(stack) == 0) {
        return '\0';
    }
    currentIndex = length - index;// current index of the history
    return stack[length - index]; // return from the last
}

char *returnPeek(char stack[COMMAND_LINE_SIZE][COMMAND_LINE_SIZE], int numberOfMinus) {
    int length = get2dArrayLength(stack);
    if(numberOfMinus + currentIndex > length - 1) {
        return stack[length - 1];
    }

    if(length == 0) {
        return '\0';
    }

    return stack[currentIndex + numberOfMinus];
}

// Function to concatenate two strings
void strcat_custom(char *dest, char *src) {
    // Move to the end of the destination string
    while (*dest != '\0') {
        dest++;
    }
    
    // Copy characters from the source string to the end of the destination string
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    
    // Null-terminate the resulting string
    *dest = '\0';
}

int getSizeHelp() {
    return sizeof(help) / sizeof(help[0]);
}

int getSizeSetColor() {
    return sizeof(setcolor) / sizeof(setcolor[0]);
}

int getSizeCommand() {
    return sizeof(commands) / sizeof(commands[0]);
}

int find_set_color_index(char *stack[COMMAND_LINE_SIZE], char *target) {
    int length = getSizeSetColor();
    for(int i = 0; i < length; i++) {
            if (strncmp_custom(stack[i], target, getLength(target)) == 0) { // check if the string is mentioned
                return i;
            }
        }
    return -1;
}

int find_string_help_index(char *stack[COMMAND_LINE_SIZE], char *target) {
    int length = getSizeHelp();
    for(int i = 0; i < length; i++) {
            if (strncmp_custom(stack[i], target, getLength(target)) == 0) { // check if the string is mentioned
                return i;
            }
        }
    return -1;
}

char *get_help_by_index(char stack[COMMAND_LINE_SIZE][COMMAND_LINE_SIZE], int index) {
    if (index >= 0 && index < getSizeHelp()) {
        return help[index];  // Return the address of the string at the given index
    } else if(index > getSizeHelp() - 1) {
        index = 0;
        return help[0];  // Return NULL if the index is out of bounds
    }
}

char *get_set_color_index(char stack[COMMAND_LINE_SIZE][COMMAND_LINE_SIZE], int index) {
    if (index >= 0 && index < getSizeSetColor()) {
        return setcolor[index];  // Return the address of the string at the given index
    } else if(index > getSizeSetColor() - 1) {
        index = 0;
        return setcolor[0];  // Return NULL if the index is out of bounds
    }
}

int find_string_index(char *stack[COMMAND_LINE_SIZE], char *target) {
    for(int i = 0; i < getSizeCommand(); i++) {
            if (strncmp_custom(stack[i], target, getLength(target)) == 0) { // check if the string is mentioned
                return i;
            }
        }
    return -1;
}

char *get_string_index(char stack[COMMAND_LINE_SIZE][COMMAND_LINE_SIZE], int index) {
    if (index >= 0 && index < getSizeCommand()) {
        return commands[index];  // Return the address of the string at the given index
    } else if(index > getSizeCommand() - 1) {
        index = 0;
        return commands[0];  // Return NULL if the index is out of bounds
    }
}