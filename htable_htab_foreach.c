// htable_htab_foreach.c
// IJC-DU2
// Author: Miroslav Karásek, FIT
// Date: 2015-04-25

#include <stdlib.h>
#include "htable.h"

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