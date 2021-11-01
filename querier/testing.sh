#!/bin/bash
#
# Xenia Dela Cueva CS50 Lab 5
# testing.sh
# testing quierer



############################# invalid querier  ########################
 
# quierer with no arguments
./quierer
 
# quierer with one argument
./quierer ~/cs50-dev/shared/tse/output/crawler/pages-letters-depth-2/
 
# quierer with three or more arguments
./quierer ~/cs50-dev/shared/tse/output/crawler/pages-letters-depth-2/ ../outputLab5/ERRindexFilename pageDirectory
 
# quierer with both invalid arguments
./quierer ~/cs50-dev/shared/tse/invalid/ indValid
 
# quierer with noneexistent pageDirectory
./quierer ~/cs50-dev/shared/ts/output/crawler/pages-all-depth-3/ indexerOutput
 
# quierer with invalid indexFilename
./quierer ~/cs50-dev/shared/tse/output/crawler/pages-letters-depth-2/ ../outputLab5/ERRindexFilename

############################ valid indexer ########################################################################

# quierer with valid parameters
 ./quierer ~/cs50-dev/shared/tse/output/crawler/pages-letters-depth-2/  indexerOutput 
 

 # testing with VALGRIND for leaks
valgrind --leak-check=full --show-leak-kinds=all ./querier ~/cs50-dev/shared/tse/output/crawler/pages-letters-depth-2/  indexerOutput
 