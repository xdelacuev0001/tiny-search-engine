/**
 * Xenia Dela Cueva
 * CS50 21F 
 * TSE Lab 5-Indexer
 * */

#ifndef __INDEX_H
#define __INDEX_H

#include <stdio.h>
#include <stdlib.h>
#include <hashtable.h>
#include "counters.h"
#include <string.h>
#include <ctype.h>

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
 * 
 *  Note: user is responsible to get index delete
 * */
index_t* index_new(const int num_slots);

/**************** index_delete ****************/
/* Deletes an index.
 * Caller provides:
 *   a pointer to an existing index and a separate function that will be used to 
 *   iterate through the index and delete indivudal items
 * 
**/
void index_delete(index_t* index);


/******** index_read ************************/
/* Creates an index with the word as the key for the hashtable and item as its counters for its docID and counters
 * (gets a file with index format to crete into an index data structure)
 * User is responsible to get index delete
 * Caller provides:
 *   an index file with the word docID counter format
 * 
 * We return:
 *   an index with the file's information
 *   NULL if the index file was invalid
 */
index_t* index_read(char* indexFile);


/******** index_write ************************/
/* Writes into a file of "word docID counter" format using a valid index (gets an index data structure to 
 * write into file with index format)
 * Caller provides:
 *   an index 
 *   a file to write the index information
 * 
 * We return:
 *   Nothing as we write into a given file
 *   Exit(1) if there is something worng with the file or index
 * 
 */
void index_write(index_t* index, char* fileName);

/******** index_find ************************/
/* Returns the counter of an index key.
 * Caller provides:
 *   an index
 *   a key
 * 
 *  We return:
 *   NULL if key is not found
 *   the counter item associated with the key in the index
 */
void* index_find(index_t* index, char* key);

/**************** index_insert ****************/
/* Inserts a key with a given item in the index.
 * Caller provides:
 *   an index
 *   a key
 *   an item
 * 
 *  We return:
 *   false if any parameter was not found
 *   true if insertion was successful
 */
bool index_insert(index_t* index, const char* key, void* item);

#endif // __INDEX_H
