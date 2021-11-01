/**
 * Xenia Dela Cueva
 * CS50 21F 
 * TSE Lab 5-Indexer
 * */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "mem.h"


/**************** function ****************/

/* Given a word as a paremeter, it converts the word into a lowercase string
 * Caller provides:
 *   a string (assuming it does not have any non-alphabetic characters)
 *
 * Returns:
 *   the lowercase version of the string 
 *   NULL if the string given is NULL or there is a memory error
**/
char* normalize_word(const char* word);


/* Given a word as a paremeter, checks if there are any characters that are not valid
 * Caller provides:
 *   a string
 *
 * Returns:
 *   invalid character
 *   NULL if string has all alphabet characters
**/

char* is_word(char* word);



