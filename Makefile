# Makefile
# IJC-DU2 
# Author: Miroslav Karásek, FIT
# Date: 2015-04-25


# Compiler options
CC=gcc
CFLAGS=-O2 -std=c99 -pedantic -Wall -Wextra -g -fPIC
CXX=g++
CXXFLAGS=-O2 -std=c++11 -pedantic -Wall -Wextra -g -fPIC

###########################################################

all: tail tail2 wordcount wordcount-dynamic

###########################################################

tail.o: tail.c ring.h
	$(CC) $(CFLAGS) -c $< -o $@

tail2.o: tail2.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

ring.o: ring.c ring.h
	$(CC) $(CFLAGS) -c $< -o $@

wordcount.o: wordcount.c htable.h io.h
	$(CC) $(CFLAGS) -c $< -o $@

wordcount2.o: wordcount.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

io.o: io.c io.h
	$(CC) $(CFLAGS) -c $< -o $@

htable_hash_function.o: htable_hash_function.c
	$(CC) $(CFLAGS) -c $< -o $@

htable_htab_lookup.o: htable_htab_lookup.c htable.h
	$(CC) $(CFLAGS) -c $< -o $@

htable_htab_init.o: htable_htab_init.c htable.h
	$(CC) $(CFLAGS) -c $< -o $@

htable_htab_foreach.o: htable_htab_foreach.c htable.h
	$(CC) $(CFLAGS) -c $< -o $@

htable_htab_remove.o: htable_htab_remove.c htable.h
	$(CC) $(CFLAGS) -c $< -o $@

htable_htab_clear.o: htable_htab_clear.c htable.h
	$(CC) $(CFLAGS) -c $< -o $@

htable_htab_free.o: htable_htab_free.c htable.h
	$(CC) $(CFLAGS) -c $< -o $@

htable_htab_statistics.o: htable_htab_statistics.c htable.h
	$(CC) $(CFLAGS) -c $< -o $@
	
###########################################################

libhtable.a: htable_hash_function.o htable_htab_lookup.o htable_htab_init.o htable_htab_foreach.o htable_htab_remove.o htable_htab_clear.o htable_htab_free.o htable_htab_statistics.o
	ar crs $@ $?

libhtable.so: htable_hash_function.o htable_htab_lookup.o htable_htab_init.o htable_htab_foreach.o htable_htab_remove.o htable_htab_clear.o htable_htab_free.o htable_htab_statistics.o
	$(CC) $(CFLAGS) -shared  $? -o $@

###########################################################

wordcount: wordcount.o io.o libhtable.a
	$(CC) $(CFLAGS) wordcount.o io.o -o $@ -static -L. -lhtable

wordcount-dynamic: wordcount.o io.o libhtable.so
	$(CC) $(CFLAGS) wordcount.o io.o -o $@ -L. -lhtable
	
tail: tail.o ring.o
	$(CC) $(CFLAGS) $? -o $@
	
tail2: tail2.o
	$(CXX) $(CXXFLAGS) $? -o $@