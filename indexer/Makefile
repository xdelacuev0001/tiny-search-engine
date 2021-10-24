# Makefile for the "indexer" program 
# Xenia Dela Cueva 
#CS50 

OBJS = indexer.o indextest.o
LIBS = ../common/common.a ../libcs50/libcs50-given.a

L = ../libcs50
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../libcs50 -I../common
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all


.PHONY: valgrind test all clean

all: indexer indextest

indexer: indexer.o $(LIBS)
	$(CC) $(CFLAGS) indexer.o $(LIBS) -o indexer

indextest: indextest.o $(LIBS)
	$(CC) $(CFLAGS) indextest.o $(LIBS) -o indextest


indexer.o: ../common/pagedir.h  ../common/index.h ../common/word.h $L/hashtable.h $L/webpage.h $L/mem.h $L/counters.h
indextest.o: ../common/index.h ../common/word.h $L/hashtable.h 

valgrind: crawler testing.sh
	$(VALGRIND) bash -v testing.sh


test:	testing.sh
		bash -v testing.sh

clean:
	rm -f indexer
	rm -f indextest
	rm -f *~ *.o
	rm -rf *.dSYM
	rm -f core