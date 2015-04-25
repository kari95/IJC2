// htable_htab_remove.c
// IJC-DU2
// Author: Miroslav Karásek, FIT
// Date: 2015-04-25

#include <stdlib.h>
#include <string.h>
#include "htable.h"

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