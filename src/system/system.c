#include "./system.h"
const char *commands[5] = {"help", "clear", "set -t", "set -b", "showinfo"};

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
     while (*src) {          // While the character src points to is not '\0' (not the end of the string)
        *dest = *src;       // Copy the character from src to dest
        dest++;             // Move the destination pointer to the next character
        src++;              // Move the source pointer to the next character
    }
    *dest = '\0';           // Append '\0' to the end of the string in dest
}

int strncmp_custom(const char *s1, const char *s2, int n) {
    if (n == 0) return 0;  // If n is zero, no characters are compared, and the function returns 0.

    while (n-- > 1 && *s1 && *s1 == *s2) {
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
    }
    return 0;
}

// int containSpace(char *s) {
//     int ctr = 0;
//     char tmp[COMMAND_LINE_SIZE];
//     int commandIndex = 0;
//     while(*s != '\0') {
//         if(*s == ' ') {
//             continue;
//         } else {
//             tmp[commandIndex] = *s; // Add the character to commandLine and increment index
//             commandIndex++;
//             tmp[commandIndex] = '\0'; // Null-terminate the string
//         }
//         s++;
//     }
//     return ctr;
// }

