// htable_htab_statistics.c
// IJC-DU2
// Author: Miroslav Karásek, FIT
// Date: 2015-04-25

#include <stdio.h>
#include <limits.h>
#include "htable.h"

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