// htable_htab_free.c
// IJC-DU2
// Author: Miroslav Karásek, FIT
// Date: 2015-04-25

#include <stdlib.h>
#include "htable.h"

void htab_free(htab_t *table)
{
	htab_clear(table);
	free(table);
}