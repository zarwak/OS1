// File: src/mystrfunctions.c
#include "../include/mystrfunctions.h"

// Your main task is to implement the logic for the string
// functions mentioned in the header file [cite: 86]

int mystrlen(const char* s) {
    int count = 0;
    while (s[count] != '\0') {
        count++;
    }
    return count;
}

int mystrcpy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return i;
}

int mystrncpy(char* dest, const char* src, int n) {
    int i;
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[i] = src[i];
    }
    for (; i < n; i++) {
        dest[i] = '\0';
    }
    return i;
}

int mystrcat(char* dest, const char* src) {
    int dest_len = mystrlen(dest);
    int i;
    for (i = 0; src[i] != '\0'; i++) {
        dest[dest_len + i] = src[i];
    }
    dest[dest_len + i] = '\0';
    return dest_len;
}
