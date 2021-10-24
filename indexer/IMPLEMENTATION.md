# CS50 TSE LAB 4, Updated for Lab 5
## Xenia Dela Cueva (Github usename: xdelacuev1)


# Detailed pseudo code for each of the objects/components/functions,
* Indexer
/**************** main ****************/
//parse through the arguments
//create an index from the pagedirectory
//write the index into a file
//free any unecessary memory allocations like the creatd index

/**************** parseArgs ****************/
//given three arguments 
//allocate the first given argument as pageDirectory
//check if the pageDirectory is one made by crawler 
//create an error if it is not

//allocate the second given argument as indexFilename
//make sure it is able to be written on

/**************** indexBuild ****************/
//creates a new 'index' object
//loops over document ID numbers, counting from 1
//loads a webpage from the document file 'pageDirectory/id', 
   //if successful,
   //passes the webpage and docID to indexPage


/**************** indexPage ****************/
// steps through each word of the webpage,
//skips trivial words (less than length 3),
//normalizes the word (converts to lower case),
//check if word is in the index
  //if the word is in the index,
  //check its counters if it contains the docID already
     //if the word counters does not have the given docID, add it in to the counters
          //if it does have it in the counters, increment it to one
  //if word is not in index, add word as index with counters as its item 
 
 (NOTE*: I used a helper function word_check to implement indexPage, along with normalize_word from word.h)


* Index module
/**************** index_new ****************/
//makes sure the number of slots is greater than 0
//using the index's hashtable, the int parameter will be the hashtable's # of slots
//save the index

/**************** index_delete ****************/
//delete the hashtable
//delete the index

/**************** index_find ****************/
//using the index's hashtable, 
//return the key's item if the key is in the hashtable

/**************** index_insert ****************/
//using the hashtable in the index, insert the item with a given key

/**************** index_read ****************/
//check if you can read into the given file
//create an index with slots equaling the same number of words in the file 
    //loop through each line where you allocate the word into a new key in the index
       //loop through each docID and counter pair, where you add it to each key's counter in the index

/**************** index_write ****************/
//loop through each key in the index to write down each word
  //loop through each counter of each key in the index to write each docID and counter



* Pagedir module (functions not used in crawler)
/**************** pagedir_load ****************/
//check the given file if you are able to open it
//the first line will be the url of the webpage
//second line will be the depth of the webpage
//the rest is the html file of the webpage
//convert the file into a webpage using those three variables


/**************** pagedir_verify ****************/
//check if each directory has a /.crawler
//return true if it does
//return fall if it doesn't

* Word module 

/**************** normalize_word /****************
//given a word as a parameter (which we assume is alphabetical)
//iterate through each letter of the word to make it lower case
//return the lower case version of the word



# Data structures used
typedef struct index index_t; An index only has a hashtable in its structure

Given:
typedef struct index hashtable_t;
typedef struct index counters_t;
typedef struct index webpage_t;

# Security and privacy properties/ Error handling and recovery,
I implement defensive programming in which I use if conditions to make sure that the given arguments for functions are valid (or the function exits in a standard error). Helper functions within modules like index are also made static so the user cannot access them.


# Persistent storage (files, database, etc).
Calling new data structures like hashtable, index, or counters will automatically allocate memory. I do not free memory when I am returning the structure like in functions 
* index_find
* index_read
* indexBuild
* indexPage
* word_check

# Testing plan
I will use a testing script to automatically test out indexer and indextest, starting off with invalid parameters (including but not limited to invalid number of given arguments, non existing webpages and files). I will also run it through valgrind (and leaving it out in the testing.out) to show any memory leaks