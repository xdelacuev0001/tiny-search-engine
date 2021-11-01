/**
 * Xenia Dela Cueva
 * CS50 21F 
 * TSE Lab 5-Indexer
 * 
 * index, a module providing the data structure to represent the in-memory index, and functions to read and write index files;
 * */


#include <stdio.h>
#include <stdlib.h>
#include <hashtable.h>
#include "file.h"
#include "counters.h"
#include <string.h>
#include <ctype.h>
#include "mem.h"

typedef struct index
{
  hashtable_t* hash_index; 
} index_t;


/**************** function prototypes ****************/
index_t* index_new(const int num_slots);
void index_delete(index_t* index);
index_t* index_read(char* indexFile);
void index_write(index_t* index, char* fileName);
counters_t* index_find(index_t* index, char* key);
void helper_delete(void* item);
bool index_insert(index_t* index, const char* key, void* item);


/**************** local functions ****************/
//not seen outside of this file
static void ht_writeKey(void* arg, const char* key, void* item);
static void ctrs_write(void* arg, const int key, const int count);


/**************** index_new ****************/
index_t* index_new(const int num_slots) 
{
    //makes sure the number of slots is greater than 0 
    if (num_slots <= 0) {
        fprintf(stderr,"slots must be greater than 0");
        return NULL;
    }

    else {
        index_t* index = malloc(sizeof(index_t));
        
        if (index == NULL) {
            return NULL;              // error allocating bag
            }

        else {
          //using the index's hashtable, the int parameter will be the hashtable's # of slots
            index->hash_index = hashtable_new(num_slots);
            }

            return index; 
        }
}


/**************** index_delete ****************/
//index delete
void index_delete(index_t* index) {
    if (index != NULL) {
      
      hashtable_delete(index->hash_index, helper_delete);
      }
    free(index);
  }

void helper_delete(void* item) {

  counters_t* actual;
  actual = item;
  counters_delete(actual);

}

/**************** index_find ****************/
counters_t* index_find(index_t* index, char* key) {

  if (hashtable_find(index->hash_index, key) != NULL) {

    counters_t* the_item = hashtable_find(index->hash_index, key);
    return the_item;
  }

  else {
    return NULL;
  }
}



/**************** index_insert ****************/
bool index_insert(index_t* index, const char* key, void* item) {
  if ((index !=NULL) && (key != NULL) && (item != NULL)) {
    return hashtable_insert(index->hash_index, key, item);
  }

  else {
    return false;
  }
}



/**************** index_read ****************/
index_t* index_read(char* indexFile)
{
  FILE* fp;
  fp = fopen(indexFile, "r");
  

  if (fp == NULL) {
    fprintf(stderr, "Invalid indexFile");
    return NULL;
  }

  int slots = file_numLines(fp);
    
  index_t* file_index = index_new(slots);
  char* word_key = mem_malloc(50);
  int docID = 0 ;
  int count = 0;

  //integer represents the numbers of variables allocated
  while ((fscanf(fp, "%s ", word_key)) == 1) {
    
    counters_t* new_counter = counters_new();
    hashtable_insert(file_index->hash_index, word_key, new_counter);

     while ((fscanf(fp, "%d %d ", &docID, &count)) == 2) {
       counters_set(new_counter, docID, count);
     }
     
  }
  fclose(fp);
  mem_free(word_key);

  return file_index;
}


/**************** index_write ****************/
void index_write(index_t* index, char* fileName) {
  FILE* fp;

  if (index == NULL) {
    fprintf(stderr, "Index is invalid\n");
    exit(1);

  }

  if ((fp = fopen(fileName, "w")) != NULL) {
    hashtable_iterate(index->hash_index, fp, ht_writeKey);
    fclose(fp);

  }

  else {
    fprintf(stderr, "Unable to open fileName\n");
    exit(1);
  }



}

/**************** local functions ****************/

//making all the words into keys
static void ht_writeKey(void* arg, const char* key, void* item) {
  //writing each key to each file
  FILE* fp = arg;
  fprintf(fp,"%s ", key);
  counters_t* counter = item;
  counters_iterate(counter, fp, ctrs_write);

  //into new line
  fprintf(fp, "\n");
}

static void ctrs_write(void* arg, const int key, const int count) {
  FILE* fp = arg;
  fprintf(fp,"%d %d ", key, count); //key is docID when using in IndexPage;

}