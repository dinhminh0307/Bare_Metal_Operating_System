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

int compare(char *s, char *target) {
    while (*s && *s == *target) {
        s++;
        target++;
    }
    // If both strings ended, they match, otherwise they don't
    return *s == '\0' && *target == '\0';
}


int main(void) {
    char s[100];
    printf("%d", getLength(s));
    // if(compare(s, "hello world") == 1) {
    //     printf("hello world");
    // }
    // else {
    //     printf("vcl");
    // }
}