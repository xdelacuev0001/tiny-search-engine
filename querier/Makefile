# Makefile for the "querier" program 
# Xenia Dela Cueva 
#CS50 

OBJS = querier.o 
LIBS = ../common/common.a ../libcs50/libcs50-given.a

L = ../libcs50
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../libcs50 -I../common
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all


.PHONY: valgrind test all clean

all: querier 

querier: querier.o $(LIBS)
	$(CC) $(CFLAGS) querier.o $(LIBS) -o querier



querier.o: ../common/pagedir.h  ../common/index.h ../common/word.h $L/file.h $L/mem.h $L/counters.h $L/set.h

valgrind: crawler testing.sh
	$(VALGRIND) bash -v testing.sh


test:	testing.sh
		bash -v testing.sh

clean:
	rm -f querier
	rm -f *~ *.o
	rm -rf *.dSYM
	rm -f core