/**
 * Xenia Dela Cueva
 * CS50 21F Lab 5
 * Indexer
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mem.h"


char* normalize_word(const char* word);


//a module providing a function to normalize a word.
char* normalize_word(const char* word) {
    
    if (word == NULL) {
        return NULL;
        }


    //allocating space for resulting string which will not be longer than given string
    char* norm_word = mem_malloc(strlen(word)+1);
    
    if (norm_word == NULL) {
        return NULL;
        } 
    
    else {

        //looping through the word to make each character lowercase
        for (int i = 0; i < strlen(word); i ++) {
            norm_word[i] = tolower(word[i]);

    }

    return norm_word;
    }
}


