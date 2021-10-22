/**
 * Xenia Dela Cueva
 * CS50 21F 
 * TSE Lab 5-Indexer
 * */

#ifndef __INDEX_H
#define __INDEX_H

#include <stdio.h>
#include <stdlib.h>

/**************** global types ****************/
typedef struct index index_t;  // opaque to users of the module



/**************** functions ****************/

/**************** index_new ****************/
/* Creates a new (empty) index
 * Caller provides: 
 * an integer greater than 0 representing the number of slots in the index
 *
 * We return:
 *  a pointer to an empty index
 * */
index_t* index_new(const int num_slots);

/**************** index_new ****************/
/* Deletes an index.
 * Caller provides:
 *   a pointer to an existing index and a separate function that will be used to 
 *   iterate through the index and delete indivudal items
 * 
**/
void index_delete(index_t* ind, void (*itemdelete)(void* item) );

/******** index_read ************************/
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

/******** index_read ************************/
//index read


/******** index_write ************************/
//index write