// ring.h
// IJC-DU2 2015-04-10
// Author: Miroslav Karásek, FIT

#ifndef RING_H
#define RING_H

typedef struct {
    unsigned length;
    unsigned width;
    char *read_index;
    char *write_index;
    char data[];
} ring_t;

ring_t *ring_init(unsigned length, unsigned width);

void ring_write_buffer(ring_t *ring, char *buffer);

char *ring_read_buffer(ring_t *ring);

void ring_free(ring_t *ring);

void ring_test(unsigned length, unsigned width);

#endif //RING_H