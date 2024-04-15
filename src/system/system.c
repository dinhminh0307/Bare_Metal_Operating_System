#include "./system.h"

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
    } else if(compare(s, "showinfo\n")) {
        return 4;
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

