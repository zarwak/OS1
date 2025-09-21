// File: src/myfilefunctions.c
#include "../include/myfilefunctions.h"
#include <stdlib.h>
#include <string.h>

// Your main task is to implement the logic for the file
// functions mentioned in the header file [cite: 89]

int wordCount(FILE* file, int* lines, int* words, int* chars) {
    if (file == NULL) {
        return -1; // Return -1 on failure.
    }

    *lines = 0;
    *words = 0;
    *chars = 0;
    int c;
    int in_word = 0;

    while ((c = fgetc(file)) != EOF) {
        (*chars)++;
        if (c == '\n') {
            (*lines)++;
        }
        if (c == ' ' || c == '\n' || c == '\t') {
            in_word = 0;
        } else if (in_word == 0) {
            in_word = 1;
            (*words)++;
        }
    }
    return 0; // Return 0 on success.
}

int mygrep(FILE* fp, const char* search_str, char*** matches) {
    if (fp == NULL || search_str == NULL) {
        return -1; // Return -1 on failure.
    }

    // You will need to implement this function to read lines, search for the substring,
    // and allocate memory for the matches. A good approach would be to:
    // 1. Initialize a dynamic array to hold the matched lines (e.g., using a realloc-based approach).
    // 2. Read the file line by line (e.g., using fgets).
    // 3. Check if the line contains the search_str (e.g., using strstr).
    // 4. If a match is found, duplicate the line (e.g., using strdup) and add it to your dynamic array.
    // 5. Update the count of matches and return it at the end.
    // Remember to rewind the file pointer at the start if it's not already at the beginning.

    // A simple, incomplete example for structure:
    // char* line = NULL;
    // size_t len = 0;
    // int matches_count = 0;
    // *matches = NULL;
    // while (getline(&line, &len, fp) != -1) {
    //     if (strstr(line, search_str) != NULL) {
    //         *matches = realloc(*matches, (matches_count + 1) * sizeof(char*));
    //         (*matches)[matches_count] = strdup(line);
    //         matches_count++;
    //     }
    // }
    // free(line);
    // return matches_count;
    // Note: This is just a conceptual outline. You will need to complete this logic.
    return 0;
}
