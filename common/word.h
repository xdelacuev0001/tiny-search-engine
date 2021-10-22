/**
 * Xenia Dela Cueva
 * CS50 21F 
 * TSE Lab 5-Indexer
 * */

#ifndef __WORD_H
#define __WORD_H

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



