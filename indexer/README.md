# CS50 TSE LAB 4, Updated for Lab 5
## Xenia Dela Cueva (Github usename: xdelacuev1)


### indexer
To keep track the amount of times a word has occured in a webpage, indexer is used to store a hashtable (encapsulated in an index) with words and store which docIDs it has been in and how many times did it appear.


### Usage

Indexer takes in pageDirectories specifically from directories that crawler made. It then takes the words from docIDs and stores it in an index where the word is the key. Words will be unique and lowercased and can hold many docIDs, storing how many times it occured in each docID. Indextest will test out reading and writing indexFiles, in which it will test if it can recreate an index given a written file in the index format. Indexer and indextest will also test out if it can write a file in index format.



### Assumptions
We assume words take in from the pageDirectory are not greater than 50 bytes. We also assume that recreating indexes like in
indextest does not fully recreate files in order, but rather the same information. Indexfiles given to index_read function are assumed to be in the index format (word docID counter...) to be able to recreate the index


### Files

* `Makefile` - compilation procedure
* `indexer.c` - the implementation of pagedir
* `indextest.h` - the interface of pagedir
* `testing.sh` - testing script
* `testing.out` - testing output


### Compilation

To compile, simply `make`.
To test, simply `make test`.
To clean, simply `make clean`.
