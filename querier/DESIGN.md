# CS50 TSE LAB 6
## Xenia Dela Cueva (Github usename: xdelacuev1)
  
  

* User interface
For querier to work, the command must give 2 valid arguments

quierer pageDirectory indexFilename

For example the command:

quierer ~/cs50-dev/shared/tse/output/crawler/pages-toscrape-depth-1/ ../outputLab5/indexerOutput

pageDirectory refers to a directory of webpage files made by crawler. indexFilename refers to an existing file in which an index is written in a specific format that can be read by index.



* Inputs and outputs
Inputs are mainly from the user, which we will use Standard In (stdin) as inputs. For every line the user writes, we will consider that as a query. As an output, we will provide documents that contain the query, ranking them by scores in decreasing order. Our output will be in the format of the score, the docID, and then the URL. If no documents supply the query, we write "No Documents Match". If it is a white space input, output will be blank.


* Functional decomposition into modules


   1. main to run the entire querier 
   2. parseArgs to validate the initial command
   3. validation of query (a set of functions) to split the lines and validate each word before searching them in our querier
   4. querer_builder that takes in the set of words, separates it into subsets if an "or" is seen in the query and builds the counter of scores
   5. rank_scores to rank the counter of scores in decreasing order



* Pseudo code (plain English-like language) for logic/algorithmic flow

//prompt the user to give a query of words
//we will consider every the words a set until the next line
//split the words into an array
//then parse through the words to validate them and the line
//subset the word array if the word "or" is seen 
//for each subset of words, create a counter where the keys are the doc IDs and the items are the scores (both have to be integers)//loop through each words in a subset to find their minimum occurences per docID, using a counter to represent a subset
//keep these in a set (where the index of the beginning word per subset in the line is the key since we can gurantee that no index will be the same)
//unionize all the counters in the set of subset counters to get the final counter of query results

//once you are done with the counters, sort it in decreasing order
//loop through the keys of the counter to do this, starting with the highest counter item first
//first print the score (which is the item of the key with the highest score)
//then print the key (the docID)
//(then print the url, which you get from getting from the pageDirectory and read the first line of the file)
//these can all be in one line



* Major data structures

I created a struct called scorer in which scorer holds 3 counters, one set, the word line, the number of words in the word line, and the index to refer to when creating the scores. To be able to compare more than one counter using the counter iterator, the counters will be manipulated.

I also created a struct called rank that holds the key as the docID for the highest score for the query and count for the score. I also hold in the page directory and the counters where we had all the scores.

* Testing plan 

I will run the code useing valid arguments for pageDirectory and indexFilename and providing several examples in stdin.

  
  
  
  
  
  
  
  
  
  
  
  
  
  