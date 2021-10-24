/**
 * Xenia Dela Cueva
 * CS50 21F 
 * TSE Lab 5-Indexer
 * Using a page directory from crawler, will create index files for each word
 * */



#include <stdio.h>
#include <stdlib.h>

#include "pagedir.h"
#include "hashtable.h"
#include "index.h"
#include "word.h"
#include "webpage.h"
#include "counters.h"
#include "mem.h"
#include <string.h>
#include <ctype.h>



/******************** function prototypes *********************/
static void parseArgs(const int argc, char* argv[], char** pageDirectory , char** indexFilename);
index_t* indexBuild(const char* pageDirectory);
index_t* indexPage(index_t* index, webpage_t* webpage, int docID);
index_t* word_check(char* word, int docID, index_t* index);


//main, which parses arguments and initializes other modules;
int
main(int argc, char* argv[])
{
    char* indexFilename = NULL;
    char*  pageDirectory = NULL;
    parseArgs(argc, argv, &pageDirectory, &indexFilename);
    index_t* index = indexBuild(pageDirectory);
    index_write(index, indexFilename);

    index_delete(index);
    

}

static void parseArgs(const int argc, char* argv[], char** pageDirectory , char** indexFilename)
{ 
    //makes sure that there are 3 arguements 
    //indexer pageDirectory indexFilename
    FILE* fp; 

    if (argc != 3) {
        fprintf(stderr, "Invalid number of given arguments\n");
        exit(1);

    }

    *pageDirectory = argv[1];
    *indexFilename = argv[2];


    if (!pagedir_verify(*pageDirectory)) {
        fprintf(stderr, "Invalid page directory given\n");
        exit(1);

    }
    
    fp= fopen(*indexFilename, "w");

    if (fp == NULL) {
        fprintf(stderr, "File not open for writing\n");
        exit(1);

    }

    fclose(fp);



}

//indexBuild, which builds an in-memory index from webpage files it finds in the pageDirectory;
index_t* indexBuild(const char* pageDirectory)
{  
    FILE* fp;
    int slots = 500;

    //creates a new 'index' object
    index_t* index = index_new(slots); 

    if (index == NULL) {
        fprintf(stderr, "Unable to create index\n");
        exit(1);
    }

    //loops over document ID numbers, counting from 1
    int docID = 1;
    char* file_path = mem_malloc(sizeof(char)* strlen(pageDirectory) + 10);
    sprintf(file_path, "%s/%d", pageDirectory, docID);

    //loads a webpage from the document file 'pageDirectory/id', 
    while ((fp=fopen(file_path, "r"))!= NULL) {

        //if successful,
        webpage_t* page_word = NULL; 

        if ((page_word = pagedir_load(file_path)) != NULL) {

            //passes the webpage and docID to indexPage
            indexPage(index, page_word, docID);
            docID++; 
            sprintf(file_path, "%s/%d", pageDirectory, docID);
            webpage_delete(page_word); 
        }

        else {
            fprintf(stderr, "Unable to create index with file \n");
            exit(1);
        }
        fclose(fp);

    }
    mem_free(file_path);
    return index;
}

//indexPage, which scans a webpage document to add its words to the index.
index_t* indexPage(index_t* index, webpage_t* webpage, int docID) {

    if (docID < 1) {
        fprintf(stderr, "Invalid ID \n");
        exit(1);
    }

    if ((index != NULL) || (webpage != NULL) ) {
        int pos = 0;
        char* result = NULL;
        char* lower_result = NULL;

        // steps through each word of the webpage,
        while ((result = webpage_getNextWord(webpage, &pos)) != NULL) {

            //skips trivial words (less than length 3),
            if (strlen(result) < 3) {
                mem_free(result);
                continue;
            }
            //normalizes the word (converts to lower case),
            lower_result = normalize_word(result);
            word_check(lower_result, docID, index); //helper function that checks the set and counters 
            mem_free(result);
            mem_free(lower_result);


        
    }
    }

    else {
        fprintf(stderr, "Invalid Parameters: check index or webpage \n");
        exit(1);

    }

    return index;
    
}


//helper function word_check 
index_t* word_check(char* word, int docID, index_t* index)
{
    if ((word == NULL) || (index) == NULL) {
        fprintf(stderr, "Invalid Parameters: check index or word \n");
        return NULL;
    }

    if (docID < 0) {
        fprintf(stderr, "Invalid docID  \n");
        return NULL;
    }

    counters_t* word_counter = NULL;

    //check if word is in the index
    //if the word is in the index,
    if ((word_counter = index_find(index, word)) != NULL) { 


        //check its counters if it contains the docID already

        //if the word counters does not have the given docID, add it in to the counters
        if (counters_get(word_counter, docID) == 0) {
            counters_add(word_counter, docID);
        }

        //if it does have it in the counters, increment it to one
        else {
            int current_wc = counters_get(word_counter, docID) + 1;
            counters_set(word_counter, docID, current_wc);
        }
    }

    else {
        //if word is not in index, add word as index with counters as its item 
        counters_t* new_counter = counters_new();
        counters_add(new_counter, docID);
        index_insert(index, word, new_counter);

    }

    return index;

}
