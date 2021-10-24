/**
 * Xenia Dela Cueva
 * CS50 21F 
 * TSE Lab 5-Indexer
 * */

#include <stdio.h>
#include <stdlib.h>
#include "index.h"
#include "word.h"
#include "hashtable.h"


//Tests indexer with the format ./indextest oldIndexFilename newIndexFilename
int
main(int argc, char* argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Invalid number of parameters");
        exit(1);
    }

    else {
            char* existingIndex = NULL;
            char* makeIndex = NULL;
            existingIndex = argv[1];
            makeIndex = argv[2];

        // it reads an index file into the internal index data structure, then writes the index out to a new index file.
        //argv[1] = oldIndexFilename is existing index file
        index_t* index_made = index_read(existingIndex); 

        //use the index structure and write into a new file
        index_write(index_made, makeIndex); //where argv[2] is the file where we write into
    
        index_delete(index_made);

    }
}
