// wordcount.c
// IJC-DU2
// Author: Miroslav Karásek, FIT
// Date: 2015-04-18

#include <stdio.h>
#include "htable.h"
#include "io.h"

#define MAX_WORD_LENGTH 127
#define HASH_TABLE_SIZE 100

void print_item(const char *key, int value)
{
    printf("%s\t%d\n", key, value);
}

int main()
{
    char word[MAX_WORD_LENGTH + 1];
    int count;
    bool in_limit = true;
    htab_t *table = htab_init(HASH_TABLE_SIZE);
    if (table == NULL)
    {
        fprintf(stderr, "Allocation error\n");
        return 1;
    }
    while ((count = fgetw(word, MAX_WORD_LENGTH + 1, stdin)) != EOF)
    {
        if (count >= MAX_WORD_LENGTH + 1)
        {
            if (in_limit)
                fprintf(stderr, "Word is too long, limit is %d characters\n", MAX_WORD_LENGTH);
            in_limit = false;
        }
        htab_lookup(table, word)->value ++;
    }
    //htab_statistics(table);
    htab_foreach(table, print_item);
    htab_free(table);
    return 0;
}