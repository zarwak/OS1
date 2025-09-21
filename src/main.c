// File: src/main.c
#include <stdio.h>
#include <string.h>
#include "../include/mystrfunctions.h"
#include "../include/myfilefunctions.h"

int main() {
    printf("-- Testing String Functions ---\n");
    // Add code here to test each of your string functions. [cite: 95]
    char str1[50] = "Hello, world!";
    char str2[] = "programming";
    char str3[50];
    char str4[50] = "Test string for mystrncpy";

    // Test mystrlen
    printf("Length of \"%s\" is %d\n", str1, mystrlen(str1));

    // Test mystrcpy
    mystrcpy(str3, str1);
    printf("mystrcpy result: %s\n", str3);

    // Test mystrncpy
    mystrncpy(str3, str4, 10);
    str3[10] = '\0'; // Null-terminate after n characters
    printf("mystrncpy result: %s\n", str3);

    // Test mystrcat
    mystrcat(str1, str2);
    printf("mystrcat result: %s\n", str1);

    printf("\n--- Testing File Functions ---\n");
    // Add code here to test your file functions. [cite: 97]
    FILE* file = fopen("testfile.txt", "w+");
    if (file == NULL) {
        perror("Error creating test file");
        return 1;
    }
    fprintf(file, "This is a test file.\nIt has a few lines.\nAnd some words.\n");
    fseek(file, 0, SEEK_SET);

    int lines = 0, words = 0, chars = 0;
    int result = wordCount(file, &lines, &words, &chars);

    if (result == 0) {
        printf("Word Count Results:\n");
        printf("Lines: %d\n", lines);
        printf("Words: %d\n", words);
        printf("Characters: %d\n", chars);
    } else {
        printf("Error calling wordCount.\n");
    }

    // Don't forget to close the file!
    fclose(file);

    return 0;
}
