#!/bin/bash
#
# Xenia Dela Cueva CS50 Lab 5
# testing.sh
# testing indexer and indextest


# format of indexer pageDirectory indexFilename
#!/bin/bash
#
# Xenia Dela Cueva CS50 Lab 5
# testing.sh
# testing indexer and indextest
 


############################# invalid indexer  ########################
 
# indexer with no arguments
./indexer
 
# indexer with one argument
./indexer ~/cs50-dev/shared/tse/output/crawler/pages-letters-depth-2/
 
# indexer with three or more arguments
./indexer ~/cs50-dev/shared/tse/output/crawler/pages-letters-depth-2/ ../outputLab5/ERRindexFilename pageDirectory
 
./indexer ~/cs50-dev/shared/tse/output/crawler/pages-letters-depth-2/ ../outputLab5/ERRindexFilename ../outputLab5/ERRindexFilename
 
# indexer with both invalid arguments
./indexer ~/cs50-dev/shared/tse/invalid/ indValid
 
# indexer with noneexistent pageDirectory
./indexer ~/cs50-dev/shared/ts/output/crawler/pages-all-depth-3/ ../outputLab5/indexerOutput
 
# indexer with non-crawler pageDirectory
./indexer ../outputLab5/ ../outputLab5/indexerOutput
 
# indexer with invalid indexFilename
./indexer ~/cs50-dev/shared/tse/output/crawler/pages-letters-depth-2/ ../outputLab5/ERRindexFilename
 
# indexer with read-only directory read-only file
./indexer ~/cs50-dev/shared/tse/output/crawler/pages-letters-depth-2/ ../outputLab5/readonlyFile

############################ valid indexer ########################################################################

# indexer with valid parameters
 ./indexer ~/cs50-dev/shared/tse/output/crawler/pages-letters-depth-2/  ../outputLab5/indexerOutput
 ./indexer ~/cs50-dev/shared/tse/output/crawler/pages-toscrape-depth-1/  ../outputLab5/indexerOutput2

 # testing with VALGRIND for leaks
valgrind --leak-check=full --show-leak-kinds=all ./indexer ~/cs50-dev/shared/tse/output/crawler/pages-letters-depth-2/  ../outputLab5/indexerOutput
 
 
############################# invalid indextest ########################
 
# indextest with no arguments
./indextest
 
# indextest with only 1 arguments
./indextest ../outputLab5/indexerOutput
 
# indextest with 3 arguments
./indextest ../outputLab5/indexerOutput2 ../outputLab5/indextestOutput2 ../outputLab5/indextestOutput3


############################# valid indextest ########################
# indextest with valid parameters
./indextest ../outputLab5/indexerOutput ../outputLab5/indextestOutput
./indextest ../outputLab5/indexerOutput2 ../outputLab5/indextestOutput2


# testing with VALGRIND for leaks
valgrind --leak-check=full --show-leak-kinds=all ./indextest ../outputLab5/indexerOutput ../outputLab5/indextestOutput



#to compare
~/cs50-dev/shared/tse/indexcmp ../outputLab5/indexerOutput ../outputLab5/indextestOutput



