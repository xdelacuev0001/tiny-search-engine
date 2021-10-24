# Makefile for the common.a library used for TSE labs
# Inspired by knowledge unit about Makefiles and libraries
# Xenia Dela Cueva 
# 21F CS50 Lab4, Updated for Lab 5 


L = ../libcs50
# object files, and the target library
OBJS = pagedir.o index.o word.o ../libcs50/webpage.h
LIB = common.a


CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS) -I$L
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

# Build $(LIB) by archiving object files
$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)


# Dependencies: object files depend on header files
pagedir.o:	pagedir.h
index.o:	index.h
word.o:		word.h


.PHONY: clean

# clean up after our compilation
clean:
	rm -f core
	rm -f $(LIB) *~ *.o



