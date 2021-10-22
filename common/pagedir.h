/*
Xenia Dela Cueva 
CS 50 21F Lab 5
Pagedir provides functions for writing files of webpage content 
and converting files to its webpage
**/

#ifndef __PAGEDIR_H
#define __PAGEDIR_H

#include <stdio.h>
#include <stdlib.h>

/**************** functions ****************/
/******** pagedir_init ************************/
/* Initializes the pageDirectory for file writing by crawler
 *
 * Caller provides:
 *   an existing page directory
 *
 * We return:
 *   true if we are able to open and close a file
 *   false if we are unable to open the file
 */
bool pagedir_init(const char* pageDirectory);

/******** pagedir_save ************************/
/* Writes the contents of a webpage to the apporpriate file in a given directory
 *
 * Caller provides:
 *   an existing page directory
 *   a valid webpage
 *   a valid docID
 */
void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID);

/******** pagedir_load ************************/
/* Load webpages from files in the pageDirectory creating webpages from the in the pageDirectory
 *  (this is used for indexer to be able to find iterate through words easier with functions in webpage.c )
 * 
 * Caller provides:
 *   a valid file
 * 
 * We return:
 *   a webpage of the html of that file
 *   NULL if the file could not be loaded or is NULL
 *   Note: the depth and url of the file is not included into the webpage, as we intend this function to be used by indexer
 *   which wants words
 * 
 * We Assume:
 *   the file parameter is from a directory that is made by crawler
 * 
 */
webpage_t* pagedir_load(FILE* file);

/******** pagedir_verify ************************/
/* Verifies that the given pageDirectory is one made by crawler
 * Caller provides:
 *   a valid pageDirectory
 * 
 * We return:
 *   true if the pageDirectory is made by crawler
 *   false if the pageDirectory does not include a /.crawler (an indication that it is made by crawler)
 * 
 * We Assume:
 *    the crawler function given is properly working
 * 
 */
bool pagedir_verify(const char* pageDirectory);
