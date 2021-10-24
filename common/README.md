# CS50 TSE LAB 4, Updated for Lab 5
## Xenia Dela Cueva (Github usename: xdelacuev1)


### common
A library to encapsulate all the knowledge about how to initialize and validate a pageDirectory, and how to write and read page files, how to mkae words lowercase, and the creating of an index (the datastructure that will be used to keep track of a word's appearance in one or more file) in one place.


### Usage

Currently, there is only three modules in the common directory, which is pagedir, word and index. The word module recreates a word string into a lowercase one. The index module keeps track of all the words from one or more file, using a hashtable to make the words as keys and its item a set of counters that keeps track of how many times that word appered an a certain file.

### Assumptions

 We assume that the given parameter for word does not have non-alphabet characters. Therefore another assumption we make is that there are no repeating words in an index. We also assume that a word is no longer than 50 bytes (as we memory allocated 50) for it.

### Files

* `Makefile` - compilation procedure
* `pagedir.c` - the implementation of pagedir
* `pagedir.h` - the interface of pagedir
* `index.c` - the implementation of index
* `index.h` - the interface of index
* `word.c` - the implementation of word
* `word.h` - the interface of word


### Compilation

To compile, simply `make`.
