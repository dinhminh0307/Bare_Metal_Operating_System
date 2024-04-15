
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

int containSpace(char *s) {
    int ctr = 0;
    while(*s != '\0') {
        if(*s == ' ') ctr++;
        s++;
    }
    return ctr;
}


int main(void) {
    char *s = "hello world  ";
    printf("%d", containSpace(s));
    // if(compare(s, "hello world") == 1) {
    //     printf("hello world");
    // }
    // else {
    //     printf("vcl");
    // }
}
