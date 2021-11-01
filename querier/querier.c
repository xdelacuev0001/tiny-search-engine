/**
 * Xenia Dela Cueva
 * CS50 21F 
 * TSE Lab 6-Querier
 * 
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "counters.h"
#include "set.h"
#include "index.h" //like index test, need to create index using page directory from crawler with index build
#include "pagedir.h" //need to verify that pageDirectory is made by crawler
#include "file.h" //use to get fro each file in the page directory, the first line for the url using readline function
#include "mem.h" // to allocate and release memory
#include "word.h" //to normalize each word from query

//if using or, the score is the sum of both separate occurences in each file
//if using and, the score is the minimum score of either word a or b


typedef struct scorer
{
  counters_t* sum; //to keep trank of the total score of each docID
  counters_t* factor; //a counter to help implement "and" sequencing
  counters_t* ctr_keeper; //to keep each sub query (grouping the words separated by or)
  set_t* subset_queries; //keeping track of the subqueries that are already minimized docs
  char** word_set; //keeping track of the 
  int* num_set; //the number of items in the set
  index_t* index;

} scorer_t;

typedef struct ranker
{
  int key; //docID
  int count; //will be used to compare scores for docIDs
  char* pageDirectory;
  counters_t* score;

} ranker_t;

/********************************* function prototypes *************************/
static void parseArgs(const int argc, char* argv[], char** pageDirectory , char** indexFilename);
void line_splitter(char* each_line, char** word_set, int* current);
void validate_query(scorer_t* scorer);
void normalize_query(scorer_t* scorer);
bool andor_validate(scorer_t* scorer);
void querer_builder(scorer_t* scorer);

void ctrs_sqHelper(void* arg, const int key, const int count);
void set_scorefunc(void* arg, const char* key, void* item);
void counters_andfunc(void* arg, const int key, const int count) ;
void counters_orfunc(void* arg, const int key, const int count) ;
void set_delhelper(void* item);

void scorer_delete(scorer_t* scorer) ;
void rank_scores(scorer_t* scorer, char** pageDirectory);
void print_max(void* arg, const int key, const int count);
void get_max(void* arg, const int key, const int count);
void URL_printer(const int key, char** pageDirectory) ;


int
main(int argc, char* argv[])
{

    char* indexFilename = NULL;
    char*  pageDirectory = NULL;

    parseArgs(argc, argv, &pageDirectory, &indexFilename); //validate given arguments

    index_t* index = index_read(indexFilename); //create an index with the indexFile

    printf("\nTo start querier, provide words to look up\n"); //then prompt the user to give a query of words
    
    char* line = file_readLine(stdin);
    while (line != NULL) {

        //assuming the worst, the word array will be the size of the line size/2 (accounting for white space)
        int mem_size = (strlen(line) /2) + 1;
        char* word_set[mem_size]; 
        int num_inSet = 0;


        line_splitter(line, word_set, &num_inSet); //split the line into words

        //creating a scorer which keeps track of the words and counters to make query
        scorer_t query_initial = {counters_new(), counters_new(), counters_new(), set_new(), word_set, &num_inSet, index};

        validate_query(&query_initial); //check for any bad characters in the words
        normalize_query(&query_initial); //lowercase all the words

        //the query to use
        querer_builder(&query_initial);
        
        if ((query_initial.sum) == NULL) {
            printf("No documents match your query\n");
            printf("Cleaning search\n");
            printf("Enter new query\n");
            line = file_readLine(stdin);
            }

        rank_scores(&query_initial, &pageDirectory);

        printf("Cleaning search\n");
        printf("Enter new query\n");
        scorer_delete(&query_initial);
        //scorer_delete(query_initial);

        line = file_readLine(stdin);

    }

    printf("Querier quits...\n");
}

//step one: parse args that indexFile can be made into a valid index and pageDirectory is a directory made by crawler
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
    
    fp= fopen(*indexFilename, "r");

    if (fp == NULL) {
        fprintf(stderr, "Indexfile not cannot be read\n");
        exit(1);
    }

    fclose(fp);
}

/* Parses the line into word sets */
void line_splitter(char* each_line, char** word_set, int* current) 
{
    //initializing that word set is the whole line
    word_set[*current] = each_line;

    for (char* i = each_line; *i != '\0'; ) {
        char* new_word = NULL;
        
        //to ignore the white space
        while (isspace(*i)) {
            i++;}

        if (*i != '\0') { //point to next existing character
            new_word = i;}

        while ((!isspace(*i)) && (*i != '\0')) {
            i++;}

        if (*i != '\0') { //when it sees a space, add a terminating null to the end of the pointer for one word
            *i = '\0';
            i++;}

        if (new_word != NULL) {
            word_set[*current] = new_word; //add word into our set
            (*current)++; }
    }
}

/******************* checks each word in the word set to make sure all are alphabetic characters **********/
void validate_query(scorer_t* scorer) 
{

    if (scorer->num_set == NULL && scorer->word_set) {
        fprintf(stderr,"Error: Must initialize the numbers and word set through scorer first\n");
    }

    char* inv_char;
    for (int i=0; i < *scorer->num_set; i++) {
        //if there is an invalid character identified
        if ((inv_char = is_word(scorer->word_set[i])) != NULL) {
            fprintf(stderr, "Error: bad character '%s' in query.\n", inv_char);
        }
        else {
            continue;
        }
        
    }
}

/******************* goes through the words to make it lowercase **********/
void normalize_query(scorer_t* scorer)
{

    if (scorer->num_set == NULL && scorer->word_set) {
        fprintf(stderr,"Error: Must initialize the numbers and word set through scorer first\n");
    }

    for (int i=0; i < *scorer->num_set; i++) {
        scorer->word_set[i] = normalize_word(scorer->word_set[i]);

    }

}

bool andor_validate(scorer_t* scorer)
{
    int last = *scorer->num_set - 1;

    
    char* start_word = scorer->word_set[0];
    char* end_word = scorer->word_set[last];

    //check that "and" or "or" are not the beginning or end of the word set
    if (strcmp(start_word, "and") == 0 || strcmp(start_word, "or") == 0 || strcmp(end_word, "and") == 0 || strcmp(end_word, "or") == 0 ) {

        if (strcmp(start_word, "and") == 0) {
            fprintf(stderr, "Error: %s cannot be first\n", start_word);
            return false;
        }

        if (strcmp(start_word, "or") == 0) {
            fprintf(stderr, "Error: %s cannot be first\n", start_word);
            return false;
        }

        if (strcmp(end_word, "and") == 0) {
            fprintf(stderr, "Error: %s cannot be last\n", end_word);
            return false;
        }

        if (strcmp(end_word, "or") == 0) {
            fprintf(stderr, "Error: %s cannot be last\n", end_word);
            return false;
        }
    } 
    return true;
}

void querer_builder(scorer_t* scorer) {

    if (scorer == NULL) {
        fprintf(stderr, "Error: Cannot find results of query b/c of invalid scorer\n ");
    }

    if (scorer->index == NULL) {
        fprintf(stderr, "Error: Cannot find results of query b/c of invalid index\n ");
    }

    if (andor_validate(scorer)) {
        //making the ranges to set the score
        int i = 0;
        bool after_or= true;
    
        while (i < *scorer->num_set)  {

            int start =0;
            
            //if the current word is after an "or" word
            if (after_or) {
                start = i;
                after_or = false; }
                
            if (strcmp(scorer->word_set[i], "or") == 0) {
                counters_set(scorer->ctr_keeper, start, i);
                after_or = true; 
                }
            
            i++;
        }
    
        
        //now that we have updated the set_keeper counter, we will iterate it to make each subquery, and ctrs_sqHelper
        //will add thay to the set in scorer
        counters_iterate(scorer->ctr_keeper, scorer, ctrs_sqHelper); 
        
        //once the set has all the subqueries, we will iterate through the set to unionize them
        set_iterate(scorer->subset_queries, scorer, set_scorefunc);

    }
}



//this is like a nested loop where the function goes through every word subset to create a subset query and adds it to a set

void ctrs_sqHelper(void* arg, const int key, const int count) 
{
    scorer_t* scorer = arg;
    
    // int start = key and end= item
    int start = key;
    int end = count;

    for (int i=start ; i <= end; i++ ) {
        
        char* word = scorer->word_set[i];

        //skip through "and" and "or"s because we don't want to have it part as our query results
        if (strcmp(word,"and") == 0 || strcmp(word,"or")== 0) {
            continue;
        }

        else {
            //once you have that word, find it in the index. 
            //If index does have the word, keep it in scorer->factor counter.
            counters_t* factor = counters_new();
            if ((factor =index_find(scorer->index, word)) != NULL) {

                //if the index has the word, it will return us a counter 
                //we will then use the counter iterator to ensure minimums to be added into the counter->factor (like the finalized
                //query for a subset)
                counters_iterate(factor, scorer, counters_andfunc);
            }

            else {
                //If the index does not have that word, create a new empty counter
                scorer->factor = factor;
            }

        }
        //convert the start int into a string bc we can gurantee all the start indexes of the word set are unique
        char* set_key= mem_malloc(sizeof(int));;
        sprintf(set_key, "%d", start);

        //insert the counter in the subset_queries set and then renew the counter
        set_insert(scorer->subset_queries, set_key, scorer->factor);
        scorer->factor = counters_new();
        mem_free(set_key);
        }
}

//subset_query iterator
//each key represents the subset of words in a query, which we keep as a counter for the key's item
void set_scorefunc(void* arg, const char* key, void* item) {
    counters_t* counter = item;
    counters_iterate(counter, arg, counters_orfunc);
}

//the "and" iterator, deals with the factor portion of scorer
void counters_andfunc(void* arg, const int key, const int count) 
{
    //counter comparator
    scorer_t* scorer = arg;
    counters_t* counter = scorer->factor;
    int current = 0;

    //check if the counter comparator has the same key (meaning that the two counters include the same docID)
    if ((current =counters_get(counter, key)) != 0) {

        //since this is for the "and" comparator we want the minimum so if
        if (current > count) {
            //replace the count with the current 
            current = count ;
            counters_set(counter, key, current);
        }
    }

    else {
        //if the counter does not have the key docId we keep track of how it is 0 occurences
        counters_set(counter, key, 0);

    }
}


//the "or" iterator, deals with the sum part of counters, or the whole query
void counters_orfunc(void* arg, const int key, const int count) 
{
    //counter comparator
    scorer_t* scorer = arg;
    counters_t* counter = scorer->sum;
    int current = 0;
    int total = 0;

    //check if the counter comparator has the same key (meaning that the two counters include the same docID)
    if ((current =counters_get(counter, key)) != 0) {

        //since this is for the or comparator we want the sum of both
        //replace the count with the sum of both

        total = current + count;
        counters_set(counter, key, total);
    }

    else {

        //if the key is not already sum counter, then initialize it with the score of count since sum can be 
        // sum = a_score + b_score = a_score + 0
        counters_set(counter, key, count);
    }
}



void scorer_delete(scorer_t* scorer) {
    
    counters_delete(scorer->factor);
    counters_delete(scorer->sum);
    counters_delete(scorer->ctr_keeper);
    set_delete(scorer->subset_queries, set_delhelper);
}

void set_delhelper(void* item) {
    counters_t* ctrs = item;
    counters_delete(ctrs);
}


/***************** helper function to print ranked scores ************/
void rank_scores(scorer_t* scorer, char** pageDirectory)
{

    ranker_t max = {0, 1, *pageDirectory, scorer->sum};
    counters_iterate(scorer->sum, &max, print_max);

}

//helper function to print ranked scores 
void print_max(void* arg, const int key, const int count)
{
    ranker_t* max = arg;
    counters_t* score = max->score;

    counters_iterate(score, max, get_max);

   // if () {

    printf("Score: %d DocID: %d ", count, key);
    URL_printer(max->key, &max->pageDirectory);

    //}
    //once printed, set the score to zero so we don't go through it again
    counters_set(score, key, 0);

}

void get_max(void* arg, const int key, const int count)
{
    ranker_t* current_max = arg;
    if (count > current_max->count) {
        current_max->count = count;
        current_max->key = key;
    }
}

/***************** helper function to print ranked scores ************/
void URL_printer(const int key, char** pageDirectory) 
{
    FILE* fp;

    char* path = mem_malloc(sizeof(*pageDirectory)+ 10);
    sprintf(path, "%s/%d", *pageDirectory, key);
    printf("%s\n",path);

    fp = fopen(path, "r");

    if (fp == NULL) {
        fprintf(stderr, "Invalid path to get URL\n");
        exit(1);
    }
    
    char* URL =file_readLine(fp); //first line of each file
    printf("%s\n", URL);
    mem_free(URL);
    mem_free(path);
    fclose(fp);
}







