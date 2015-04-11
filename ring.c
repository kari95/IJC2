// ring.c
// IJC-DU2 2015-04-10
// Author: Miroslav Karásek, FIT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ring.h"

ring_t *ring_init(unsigned length, unsigned width)
{
    ring_t *ring;
    length++;
    ring = malloc(sizeof(ring_t) + length * width);
    if (ring != NULL)
    {
        ring->length = length;
        ring->width = width;
        ring->read_index = ring->data;
        ring->write_index = ring->data;
    }
    return ring;
}

void ring_write_buffer(ring_t *ring, char *buffer)
{
    strncpy(ring->write_index, buffer, ring->width);
    //ring->write_index[ring->width - 1] = '\0';
    ring->write_index += ring->width;
    if (ring->write_index - ring->data >= ring->length * ring->width)
        ring->write_index = ring->data;
    if (ring->read_index == ring->write_index)
    {
        ring->read_index += ring->width;
        if (ring->read_index - ring->data >= ring->length * ring->width)
            ring->read_index = ring->data;
    }
}

char *ring_read_buffer(ring_t *ring)
{
    if (ring->read_index == ring->write_index)
        return NULL;
    char *buffer = ring->read_index;
    ring->read_index += ring->width;
    if (ring->read_index - ring->data >= ring->length * ring->width)
        ring->read_index = ring->data;
    return buffer;
}

void ring_free(ring_t *ring)
{
    free(ring);
}

void ring_test(unsigned length, unsigned width)
{
    ring_t *ring = ring_init(length, width);
    if (ring == NULL)
    {
        fprintf(stderr, "Init error\n");
        return;
    }
    for (unsigned i = 0; i < 20; i++)
        ring_write_buffer(ring, "test\n");
    char *ch;
    while ((ch = ring_read_buffer(ring)) != NULL)
        printf("%s\n", ch);
    ring_free(ring);
}