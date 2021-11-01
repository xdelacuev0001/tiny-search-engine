# CS50 TSE LAB 6
## Xenia Dela Cueva (Github usename: xdelacuev1)


### Querier
To keep track the amount of times a word has occured in a webpage, indexer is used to store a hashtable (encapsulated in an index) with words and store which docIDs it has been in and how many times did it appear.


### Usage

Querier takes initially takes in a page directory made by crawler and an index filename to be able to collect data on how many times a word has appeared in a webpage (which we converted to a file). I implemented the querier with the process of splitting each query line into a set of words, validated and normalized the words, and grouped the words in a subset if we saw an "or" in the query line. I then take the minimum scores from each doc the words had existed in per subset, then combining the entire scores per docID at the end in one final counter. I then ranked these scores.

To implement this idea (more on IMPLEMENTATION. md page), I used multiple counters and counters_iterate, parsed queries in multiple functions, used isspace() and isalpha() and tried my best to do the andsequencing.


NOTE PLEASE READ
I will note that my testing.sh file is very weak and that it only showed results of what happened when I put in test cases of invalid characters and "and"/"or" in the front of queries.

Please use the command
 ./quierer ~/cs50-dev/shared/tse/output/crawler/pages-letters-depth-2/  indexerOutput 

 I think my code does run to a certain extent of showing a docID and score and URL, but I dont think it showed in my testing output. I get malloc errors. 

 I also updated my word.h file to help implement validating the words

### Assumptions
We assume that words will not be repeated in one query line. We also assume that for this to work that index file given is in the index format

### Files

* `Makefile` - compilation procedure
* `querier.c` - the implementation of pagedir
* `testing.sh` - testing script
* `testing.out` - testing output

* `word.h` - testing vesrion of word.c, which I used to add another function that validates a word, meaning that the word doesn't have any non_alphabetic characters
* `word.c` - Updated implementation with a new function called is_word. It returns a non alphabetic character

### Compilation

To compile, simply `make`.
To test, simply `make test`.
To clean, simply `make clean`.