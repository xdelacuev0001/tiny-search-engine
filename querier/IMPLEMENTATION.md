# CS50 TSE LAB 6
## Xenia Dela Cueva (Github usename: xdelacuev1)
  



* Detailed pseudo code for each of the objects/components/functions,

1. static void parseArgs(const int argc, char* argv[], char** pageDirectory , char** indexFilename);
        //make sure that the command has 2 given arguments by the user (which we consider as 3)
        //validate the pageDirectory that it is made by crawler
        //make sure the indexFilename can be read

2. void line_splitter(char* each_line, char** word_set, int* current);
        //making the entire query a character pointer
        //ignore the white space
        //point to the next existing character
        //stop when it reaches white space
        //add a terminating null to that pointer and add it to the array

3. void validate_query(scorer_t* scorer);
        //loop loop through the line of words to make sure there isn't a non-alphabetic character 
        //if there is, give an error

4. void normalize_query(scorer_t* scorer);
        //loop loop through the line of words to lower case each word

5. bool andor_validate(scorer_t* scorer);
        //loop through the line of words to make sure "and" or "or" is not in the beginning or end of the line

6. void querer_builder(scorer_t* scorer);
        //cut the word set into smaller subsets if the word "or" is seen, keeping track of them in ctr_keeper counter
        //create a counter for each subset, looping through the key and item of ctr_keeper as like a range of indices for the word set to collect the words (skipping the indices where there is "and" or "or")
        // get the minimum scores of the words per docID that the words exist in (or not)- I used counters_andfunc
        //add that subset counter in a set 
        //unionize the set of counters to get the final query- I used counters_orfunc
        (used ctrs_sqHelper, set_scorefunc to iterate through these processes)

7. void counters_andfunc(void* arg, const int key, const int count) ;
        //this compares with a counter outside of these parameters, but this function is called on with that counter 
        //per key and item of that implicit fourth parameter counter, we compare it with an existing counter in scorer (the void arg) I call factor
        //(per key and item of that implicit fourth parameter counter), if we see it in factor counter, we want to set the int item in the factor counter with the smaller number of occurences
        //if the key we gave is not in the factor counter, we still add it in but set the count to zero

8. void counters_orfunc(void* arg, const int key, const int count) ;
        //this compares with a counter outside of these parameters, but this function is called on with that counter 
        //per key and item of that implicit fourth parameter counter, we compare it with an existing counter in scorer (the void arg) I call sum
        //(per key and item of that implicit fourth parameter counter), if we see it in sum counter, we want to set the int item in the sum counter with the the overall total occurence, so adding the given count with the sum count for the key
        //if the key we gave is not in the factor counter, we still add it in and set the count whatever the count was for the key item was the fourth parameter counter

9. void scorer_delete(scorer_t* scorer) ;
        //delete any data structures and free its memory (the 3 counters, the set)

10. void rank_scores(scorer_t* scorer, char** pageDirectory);
        //initialize a rank struct with an initial max of 1 and key as 1
        //for the counter that holds the final scores for the query in scorer
        //iterate through the counters to find the max, comparing it with the count in rank (as we assume that is our max holder for the entire counter)
        //print that maximum
        //then set the count of that record in the scores_counter to zero so we do not iterate through it again
        (used print_max,get_max, and URL_printer to do this overall function )

11. void URL_printer(const int key, char** pageDirectory) ;
        //attach the given key from the counter to the end of the page directory
        //print the first line of that file

* Definition of detailed APIs, interfaces, function prototypes and their parameters
* Data structures (e.g., struct names and members)
        1. Scorer includes
            sum- the counter to keep track of the total score of each docID for all the words
            factor- a counter to help implement "and" "or" sequencing
            ctr_keeper- to keep each sub query (grouping the words separated by or) with the key as the starting index for the range in the line word set and the item count as the last word index before an "or" is seen
            subset_queries- a set of counters that holds the minimuzed scores of each subquery
            word_set- the query line that we split (we assume that this array is in order as we split it in order)
            num_set- the number of words in the query line (this just made it easier for me to loop through the words when validating it)
            index- the index used to collect the docIDs and occurences for the words

        2. Ranker includes
            key- key holder for the counter record that is considered the max
            count- the considered maximum score in the sum counter
            pageDirectory - the page directory used, which I stored in order to iterate 
            


* Error handling and recovery,
I implement defensive programming in which I use if conditions to make sure that the given arguments for functions are valid (or the function exits in a standard error). 

* Resource management
Calling new data structures like hashtable, index, or counters will automatically allocate memory. I free the sets and counters in my scorer in my main using scorer_delete

* Testing plan
I will use a testing script to automatically test out querier, starting off with invalid parameters (including but not limited to invalid number of given arguments, non existing webpages and files). The I will test different inputs to show what my program outputs.