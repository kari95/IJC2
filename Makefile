# Makefile
# IJC-DU2 
# Author: Miroslav Karásek, FIT
# Date: 2015-04-10


# Compiler options
CC=gcc
CFLAGS=-O2 -std=c99 -pedantic -Wall -Wextra -g 
LFLAGS=-lm
CPP=g++
CPPFLAGS=-O2 -std=c++11 -pedantic -Wall -Wextra -g 
LPPFLAGS=-lm -L "C:\Program Files (x86)\GCC\lib"

all: tail.exe tail2.exe wordcount.exe wordcount2.exe

tail.o: tail.c ring.h
	$(CC) $(CFLAGS) -c tail.c

tail2.o: tail2.cc
	$(CPP) $(CPPFLAGS) -c tail2.cc

ring.o: ring.c ring.h
	$(CC) $(CFLAGS) -c ring.c

htable.o: htable.c htable.h
	$(CC) $(CFLAGS) -c htable.c

wordcount.o: wordcount.c htable.h io.h
	$(CC) $(CFLAGS) -c wordcount.c

wordcount2.o: wordcount.cc
	$(CPP) $(CPPFLAGS) -c wordcount.cc -o wordcount2.o

io.o: io.c io.h
	$(CC) $(CFLAGS) -c io.c
	
wordcount.exe: wordcount.o htable.o io.o
	$(CC) $(CFLAGS) wordcount.o htable.o io.o -o wordcount.exe $(LFLAGS)
	
wordcount2.exe: wordcount2.o
	$(CPP) $(CPPFLAGS) wordcount2.o -o wordcount2.exe $(LPPFLAGS)
	
tail.exe: tail.o ring.o
	$(CC) $(CFLAGS) tail.o ring.o -o tail.exe $(LFLAGS)
	
tail2.exe: tail2.o
	$(CPP) $(CPPFLAGS) tail2.o -o tail2.exe $(LPPFLAGS)
