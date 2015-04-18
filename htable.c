// htable.c
// IJC-DU2
// Author: Miroslav Karásek, FIT
// Date: 2015-04-18

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "htable.h"

unsigned int hash_function(const char *str, unsigned htab_size) {
	unsigned int h=0;
	const unsigned char *p;
	for(p=(const unsigned char*)str; *p!='\0'; p++)
	  	h = 65599*h + *p;
	return h % htab_size;
}

htab_t *htab_init(unsigned size)
{
	htab_t *table = malloc(sizeof(htab_t) + size * sizeof(struct htab_listitem *));
	if (table != NULL)
	{
		table->size = size;
		for (unsigned i = 0; i < size; ++i)
		{
			table->data[i] = NULL;
		}
	}
	return table;
}

struct htab_listitem *htab_lookup(htab_t *table, const char *key)
{
	unsigned index = hash_function(key, table->size);
	struct htab_listitem *item = NULL;
	struct htab_listitem *before = NULL;
	for (struct htab_listitem *i = table->data[index]; i != NULL; i = i->next)
	{
		if (strcmp(i->key, key) == 0)
		{
			item = i;
		}
		before = i;
	}
	if (item == NULL)
	{	
		item = malloc(sizeof(struct htab_listitem));
		if (item == NULL)
			return NULL;
		strncpy(item->key, key, 128);
		item->value = 0;
		item->next = NULL;
		if (table->data[index] == NULL)
			table->data[index] = item;
		else
			before->next = item;
	}
	return item;
}

void htab_foreach(htab_t *table, void (*function)(const char *key, int value))
{
	for (unsigned i = 0; i < table->size; ++i)
	{
		for (struct htab_listitem *item = table->data[i]; item != NULL; item = item->next)
		{
			function(item->key, item->value);
		}
	}
}

bool htab_remove(htab_t *table, const char *key)
{
	unsigned index = hash_function(key, table->size);
	struct htab_listitem *item = NULL;
	struct htab_listitem *before = NULL;
	for (struct htab_listitem *i = table->data[index]; i != NULL; i = i->next)
	{
		if (strcmp(i->key, key) == 0)
		{
			item = i;
			if (before == NULL)
			{
				table->data[index] = item->next;
			}
			else
			{
				before->next = item->next;
			}
			free(item);
			break;
		}
		before = i;
	}
	if (item == NULL)
		return false;
	return true;

}

void htab_clear(htab_t *table)
{
	for (unsigned i = 0; i < table->size; ++i)
	{
		struct htab_listitem *next;
		for (struct htab_listitem *item = table->data[i]; item != NULL; item = next)
		{
			next = item->next;
			free(item);
		}
		table->data[i] = NULL;
	}
}

void htab_free(htab_t *table)
{
	htab_clear(table);
	free(table);
}

void htab_statistics(htab_t *table)
{
	unsigned min = UINT_MAX;
	unsigned max = 0;
	unsigned sum = 0;

	for (unsigned i = 0; i < table->size; ++i)
	{
		unsigned count = 0;
		for (struct htab_listitem *item = table->data[i]; item != NULL; item = item->next)
		{
			count++;
		}
		sum += count;
		if (count > max)
			max = count;
		if (count < min)
			min = count;

	}
	double avg = sum / table->size;
	printf("%.2f %d %d\n", avg, min, max);
}