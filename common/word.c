/**
 * Xenia Dela Cueva
 * CS50 21F Lab 5 Indexer
 * Word: a module providing a function to normalize a word.
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mem.h"

/********** function ********************/
char* normalize_word(const char* word);

/********** normalize_word ********************/
char* normalize_word(const char* word) {
    
    if (word == NULL) {
        return NULL;
        }


    //allocating space for resulting string which will not be longer than given string
    char* norm_word = mem_malloc(strlen(word)+10);
    
    if (norm_word == NULL) {
        return NULL;
        } 
    
    else {

        //looping through the word to make each character lowercase
        for (int i = 0; i < strlen(word); i ++) {
            norm_word[i] = tolower(word[i]);

    }

    int j = strlen(word);
    norm_word[j] = '\0';
    return norm_word;
    }
}

//returns the invalid character if a character is not alphabetic
char* is_word(char* word) {

    for (int i = 0; i < strlen(word); i ++) {
        if (isalpha(word[i]) == 0) {
            char* bad_char= &word[i];
            return bad_char;
        }
    }

    return NULL;
}






