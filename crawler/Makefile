# Makefile for the "crawler" program 
# Xenia Dela Cueva 
#CS50 

OBJS = crawler.o
LIBS = ../libcs50/libcs50-given.a ../common/common.a

L = ../libcs50
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../libcs50 -I../common
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

.PHONY: all clean

crawler: $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o crawler


crawler.o: ../common/pagedir.h $L/hashtable.h $L/webpage.h $L/bag.h

valgrind: crawler testing.sh
	$(VALGRIND) bash -v testing.sh


test:	crawler testing.sh
		bash -v testing.sh

clean:
	rm -f crawler
	rm -f *~ *.o
	rm -rf *.dSYM
	rm -f core

