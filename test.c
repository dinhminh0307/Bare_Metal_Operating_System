#include <stdio.h>

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

void myStrcat(char *dest, char *src) {
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

int main() {
    char *dest = "Hello";
    char *src = " World!";
    myStrcat(dest, src);
    printf("%s\n", dest);  // Output will be "Hello World!"
    return 0;
}
