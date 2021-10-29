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

#include "index.h" //like index test, need to create index using page directory from crawler with index build
#include "pagedir.h" //need to verify that pageDirectory is made by crawler
#include "file.h" //use to get fro each file in the page directory, the first line for the url using readline function
#include "mem.h" // to allocate and release memory
#include "word.h" //to normalize each word from query

//if using or, the score is the sum of both separate occurences in each file
//if using and, the score is the minimum score of either word a or b




/********************************* function prototypes *************************/
static void parseArgs(const int argc, char* argv[], char** pageDirectory , char** indexFilename);
int line_splitter(char* each_line, char** word_set);
char* validate_query(char** word_set) 

int
main(int argc, char* argv[])
{

    char* indexFilename = NULL;
    char*  pageDirectory = NULL;

    //validate given arguments
    parseArgs(argc, argv, &pageDirectory, &indexFilename);


    //create an index with the indexFile
    index_t* index = index_read(indexFilename); 

    //then prompt the user to give a query of words
    fprintf(stdout, "\nTo start querier, provide words to look up\n");

    while (!EOF) {
        char* line = file_readLine(stdin);
        line_splitter(line);


        /////////////////cutting the lines into words/////////////////////////////////

        //assuming the worst, the word array will be the size of the line size/2 (accounting for white space)

        int mem_size = (strlen(line) /2) + 1;
        char* word_set[mem_size]; 
        line_splitter(line, word_set);

        for (int i=0; i < sizeof(word_set); i++) {
        fprintf(stdout, "%s", word_set[i]);
        }

        /////////////////// validating the words in the word_set //////////////////
        if (validate(word_set) != NULL) {
            char* invalid_char = validate_query(word_set);
            fprintf(stderr, "Error: bad character '%s' in query.", invalid_char);
        }


            char** query_toUse =normalize_query(word_set);
    }

    //more to come
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

//readline from file.h to allocate the whole line of words into a a variable
//use "0\" as terminating null for each space in the array 
//iterate through all the characters in the line, so make a pointer for each character for the beginning of the word
//when it reaches the white space, it will terminate null (so you can allocate efficient memmory space for it)
//add it to an array 
//keep it together as array of character pointers
int line_splitter(char* each_line, char** word_set) 
{
    int j = 0;
    int current = 0;

    //initializing that word set is the whole line
    word_set[current] = each_line;


    //going through each character in the line
    for (int i=0; i <= (strlen(each_line)); i++) {

        //if there is a space or its the end of the line
        if (isspace(each_line[i]) != 0 || each_line[i] == '\0') { 

            //then we end the word here
            word_set[current][j] = '\0';

            //we move on to the next index of word set
            current++;
            //restart the word to a new one;
            j = 0;
            //initialize the next word
            word_set[current] = NULL;
            
        }
        else {

            word_set[current][j] = each_line[i];
            j++;
           
        }
    }

    return current;
}

char* validate_query(char** word_set) 
{


    for (int i=0; i < sizeof(word_set); i++) {

        //if there is an invalid character identified
        if (is_word(word_set[i]) != NULL) {
            return is_word(word_set[i]);
        }

        //else, normalize it
        word_set[i] = normalize_word(word_set[i]);
    }

    return NULL;
}

char** normalize_query(char** word_set)
{
    if (word_set == NULL) {
        fprintf(stderr, "Error: empty set");
        return NULL;
    }

    for (int i=0; i < sizeof(word_set); i++) {
        word_set[i] = normalize_word(word_set[i]);
    }

    return word_set;

}



//helper function that will check each word
querer_builder(index_t* index, scorer_t* scorer, char** word_set) { 

    int last = sizeof(word_set) - 1;
    

    char* start_word = word_set[0];
    char* end_word = word_set[last];

    //counters_t* scores = counters_new();

    //check that "and" or "or" are not the beginning or end of the word set
    if (strcmp(start_word, "and") == 0 || strcmp(start_word, "or") == 0) {

        if (strcmp(start_word, "and") == 0) {
            fprintf(stderr, Error: "%s" cannot be first, start_word);
            exit(1);
        }

        if (strcmp(start_word, "or") == 0) {
            fprintf(stderr, Error: "%s" cannot be first, start_word);
            exit(1);
        }
    }

    if (strcmp(end_word, "and") == 0 || strcmp(end_word, "or") == 0) {

        if (strcmp(end_word, "and") == 0) {
            fprintf(stderr, Error: "%s" cannot be last, end_word);
            exit(1);
        }

        if (strcmp(end_word, "or") == 0) {
            fprintf(stderr, Error: "%s" cannot be last, end_word);
            exit(1);
        }
    }

    //we can assume at this part that the first and last words will not be "and" or "or"
    else {
        
        counters_t* sum = counters_new();
        counters_t* factor;
        //scorer_t* scorer = scorer_new();

        //initialize the first word as our counter for our sum
        if (index_find(index, start_word) != NULL) {
            factor = index_find(index, word_set[i]);
            scorer_set(scorer, sum, factor); //both the total sum and factors are initialized with the first word's counter
            }

        int i = 1;
        int j = 0;
        int k = 0;

        while (i < last) {
            j = i -1;
            k= i + 1;

            char* factor1 = word_set[j]; //if this is the first one, we don't need to use its counters for counters iterate
            char* factor2 = word_set[k];
            counters_t* comp_factor2; 

            if ((strcmp(word_set[i], "and") == 0) || (strcmp(word_set[i], "or") == 0)) {

                //after the first word, if the next word is "and", then we get the next word after "and" to get its "factor"
                if (strcmp(word_set[i], "and") == 0) {

                    //if we are able to find the counter for the word after "and"
                    if ((comp_factor2 = index_find(index, factor2)) != NULL) {
                        counters_iterate(comp_factor2, scorer, counters_andfunc); //update the factor counter of scorer
                        counters_iterate(scorer->factor, scorer, counters_orfunc); //update the scorer sum using factor you just had
                        i = k +1; //after updating it, move on to two words after "and"
                    }

                    else {
                        //if the second word is not in the index, reset the factor counter and update the sum counter with that factor
                        scorer->factor = counters_new();
                        counters_iterate(scorer->factor, scorer, counters_orfunc);  //update the scorer sum using factor you just had
                        i = k +1; //after updating it, move on to two words after "and"
                    }
                }

                if (strcmp(word_set[i], "or") == 0) {

                    //if we are able to find the counter for the word after "or"
                    if ((comp_factor2 = index_find(index, factor2)) != NULL) {
                        counters_iterate(comp_factor2, scorer, counters_orfunc); //update the sum using the comp_factor
                        i = k+1;
                    }
                    //else if the next word is not found, do nothing to update the sum

                }
            }

            else {
                //if the next word is not "and" or "or", treat the next word like "and"
                if ((comp_factor2 = index_find(index, factor2)) != NULL) {
                    counters_iterate(comp_factor2, scorer, counters_andfunc);
                    counters_iterate(scorer->factor, scorer, counters_orfunc);
                }
            }
        }   
    }
}

typedef struct scorer
{
  counters_t* sum; 
  counters_t* factor;

} scorer_t;

scorer_new(void) 
{
  scorer_t* scorer = malloc(sizeof(scorer_t));

  if (scorer == NULL) {
    return NULL;              // error allocating set
  } 
  else {
      scorer->sum = counters_new();
      scorer->factor = counters_new();
      
      return scorer;

  }
}

scorer_t* scorer_set(scorer_t* scorer, counters_t* counters1, counters_t* counters2) 
{
    if (scorer == NULL) {
        fprintf(stderr, "Invalid scorer");
        return NULL;

    }

    if ((counters1 == NULL) || (counters2 == NULL)) {
        fprintf(stderr, "Invalid parameters to set scorer");
        return NULL;
    }
    
    scorer->sum = scorer->counters1;
    scorer->factor = scorer->counters2;
    return scorer;
}

//two types of counter iterators

//if the word and the next word are combined with "and"

//the hidden fourth parameter is where we will keep the total counters
//have an iterator for the keys
//then the two counters will be compared by its keys 
//for the matching keys (docIDs), we will set the counter

void counters_iterate(counters_t* ctrs, void* arg, 
                      void (*itemfunc)(void* arg, 
                                       const int key, const int count))

//assume there is a fourth parameter and it is the counter you call this iterator with


//the "and" iterator, deals with the factor portion of scorer
void counters_andfunc(void* arg, const int key, const int count) 
{
    //counter comparator
    scorer_t* scorer = arg;
    counters_t* counter = scorer->factor;
    int current = 0;

    //check if the counter comparator has the same key (meaning that the two counters include the same docID)
    if ((current =counters_get(counter, key)) != NULL) {

        //since this is for the and comparator we want the minimum so if
        if (current > count) {
            //replace the count with the current 
            current = count ;
            counters_set(counter, key, current);
        }
    }

    else {
        //what if the current factor has keys that is not in the counter comparator (the one we iterated with)
        //if the counter does not have the key, there is no point putting the key inside the counter
        //else you leave it alone since the comp_score is greater and we want the minimum
        counters_set(counter, key, 0);

    }
}

//the "or" iterator, deals with the sum part of counters
void counters_orfunc(void* arg, const int key, const int count) 
{
    //counter comparator
    scorer_t* scorer = arg;
    counters_t* counter = scorer->sum;
    int current = 0;
    int total = 0;

    //check if the counter comparator has the same key (meaning that the two counters include the same docID)
    if ((current =counters_get(counter, key)) != NULL) {

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







   //if it is there, iterate through the counter of the word key from the index to create those docIDs as new keys 
   //in the counter you made
   //make the occurence as the item for the docID keys
   //go on to the next word

//for the next word
// check if it is in the index if the word is there
//if it isn't, go to next word

   //if it is then decide if you will use the BNF
   //if there are additional docIDs that the word(s) is/are in, add it to the current counter with its number of occurence as item
   //if the set of words uses "and", use its minimum to add to the counter item
   //if the set uses "or", use its sum of both occurences to the counter item

   //do this until you reach to the end of the set

//once you are done with the counters, sort it using the key sort function
//loop through the keys of the counter to do this, starting with the highest counter item first
//first print the score (which is the item of the key with the highest score)
//then print the key (the docID)
//(then print the url, which you get from getting from the pageDirectory and read the first line of the file)
//these can all be in one line




}
//query builder 







//so I have an indexer 
//given a word, I check in the indexer if the word is in it.  (skipping and / or)
//if not stderr, word not found in any files of the page directory

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// dartmouth college or brown university
// if the next word after dartmouth is another word that is not "and" "or", treat it as "and"

//space is like and

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//use the page Directory to find the url for each docID
//use the indexFile to make the index


//key sort function






//then prompt the user to give a query of words
//we will consider every the words a set until there is a return button
//then parse through the words using BNF algorithm
//for each set of words, create a counter where the keys are the doc IDs and the items are the scores (both have to be integers)

//for the first word
//check in the index you made if the word is there
   //if it is not there, go to the next word

   //if it is there, iterate through the counter of the word key from the index to create those docIDs as new keys 
   //in the counter you made
   //make the occurence as the item for the docID keys
   //go on to the next word

//for the next word
// check if it is in the index if the word is there
//if it isn't, go to next word

   //if it is then decide if you will use the BNF
   //if there are additional docIDs that the word(s) is/are in, add it to the current counter with its number of occurence as item
   //if the set of words uses "and", use its minimum to add to the counter item
   //if the set uses "or", use its sum of both occurences to the counter item

   //do this until you reach to the end of the set

//once you are done with the counters, sort it using the key sort function
//loop through the keys of the counter to do this, starting with the highest counter item first
//first print the score (which is the item of the key with the highest score)
//then print the key (the docID)
//(then print the url, which you get from getting from the pageDirectory and read the first line of the file)
//these can all be in one line

//then list the score, which  document ID and URL



//don't know how to order them by order given the docID and then "the total"
//./querier pageDirectory indexFilename
//where pageDirectory is the pathname of a directory produced by the Crawler, and
//where indexFilename is the pathname of a file produced by the Indexer.
