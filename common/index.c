/**
 * Xenia Dela Cueva
 * CS50 21F 
 * TSE Lab 5-Indexer
 * */

#include <stdio.h>
#include <stdlib.h>



//index, a module providing the data structure to represent the in-memory index, and functions to read and write index files;


typedef struct index
{
  hashtable_t* hash_index; 
    
} index_t;


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

            index->hash_index = malloc(sizeof(hashtable_t));
            //hash->head = (set_t **) malloc(num_slots*sizeof(set_t *));

            index->hash_index = hashtable_new(num_slots);
            }

            return index; 
        }
}


/**************** index_delete ****************/
//index delete
void index_delete(index_t* index, void (*itemdelete)(void* item) ) {
    if (index != NULL && itemdelete != NULL) {
      
      hashtable_delete(index->hash_index, itemdelete);
      }

    //free(index->hash_index) is already freed when you call delete
    free(index);
  }

}

//index read

//index write