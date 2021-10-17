#!/bin/bash
#
# Xenia Dela Cueva CS50 Lab 4
# testing.sh
#testing crawler 

#Test the program with various forms of incorrect command-line arguments

#lack of parameters: only one parameter
./crawler 

#lack of parameters: 3 parameters
./crawler URL pagedirectory //need to fix

#URL is invlaid
./crawler invalidURL 

#all valid parameters
./crawler http://cs50tse.cs.dartmouth.edu/ ../crawltest 1

#Crawl a simple, closed set of cross-linked web pages like letters, 
#at depths 0, 1, 2, or more. Verify that the files created match expectations.
#testing at depth 0
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ ../crawltest 0

#testing at depth 1
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ ../crawltest 1

#testing at depth 2
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ ../crawltest 2

#testing at depth 3
./crawler http://cs50tse.cs.dartmouth.edu/tse/letters/ ../crawltest 3

#Repeat with a different seed page in that same site.
# If the site is indeed a graph, with cycles, there should be several interesting starting points.
#testing at depth 0
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ ../crawltest 0

#testing at depth 1
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ ../crawltest 1

#testing at depth 2
./crawler http://cs50tse.cs.dartmouth.edu/tse/wikipedia/ ../crawltest 2

#Point the crawler at one of our bigger playgrounds. Explore at depths 0, 1, 2, 
#from various starting pages. (It takes a long time to run at depth 2 or higher!) 
#Verify that the files created match expectations.
#testing at depth 0
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ ../crawltest 0

#testing at depth 1
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ ../crawltest 1

#testing at depth 2
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ ../crawltest 2

#testing at depth 3
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ ../crawltest 3

#When you are confident that your crawler runs well, test it with a greater depth - 
#but be ready to kill it if it seems to be running amok.
# testing crawler with a greater depth
./crawler http://cs50tse.cs.dartmouth.edu/tse/toscrape/ ../crawltest 5
