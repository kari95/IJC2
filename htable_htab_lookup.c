// htable_htab_lookup.c
// IJC-DU2
// Author: Miroslav Karásek, FIT
// Date: 2015-04-25

#include <stdlib.h>
#include <string.h>
#include "htable.h"

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