// htable.h
// IJC-DU2
// Author: Miroslav Karásek, FIT
// Date: 2015-04-18

#ifndef HTABLE_H
#define HTABLE_H 

#include <stdbool.h>

struct htab_listitem
{
	char key[128];
	int value;
	struct htab_listitem *next;
};

typedef struct 
{
	unsigned size;
	struct htab_listitem *data[];
} htab_t;

htab_t *htab_init(unsigned size);

struct htab_listitem *htab_lookup(htab_t *table, const char *key);

void htab_foreach(htab_t *table, void (*function)(const char *key, int value));

bool htab_remove(htab_t *table, const char *key);

void htab_clear(htab_t *table);

void htab_free(htab_t *table);

void htab_statistics(htab_t *table);

#endif