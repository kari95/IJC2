// htable_htab_init.c
// IJC-DU2
// Author: Miroslav Karásek, FIT
// Date: 2015-04-25

#include <stdlib.h>
#include "htable.h"

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