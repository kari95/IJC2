// htable_htab_clear.c
// IJC-DU2
// Author: Miroslav Karásek, FIT
// Date: 2015-04-25

#include <stdlib.h>
#include "htable.h"

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