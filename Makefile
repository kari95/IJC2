# Makefile
# IJC-DU2 2015-04-10
# Author: Miroslav Karásek, FIT


# Compiler options
CC=gcc
CFLAGS=-O2 -std=c99 -pedantic -Wall -Wextra -g 

all: tail

tail.o: tail.c ring.h
	$(CC) $(CFLAGS) -c tail.c

ring.o: ring.c ring.h
	$(CC) $(CFLAGS) -c ring.c
	
tail: tail.o ring.o
	$(CC) $(CFLAGS) tail.o ring.o -o tail -lm
