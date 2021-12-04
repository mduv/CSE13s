#include "bf.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>


struct BloomFilter {
    uint64_t primary [2]; // Primary hash function salt.
    uint64_t secondary [2]; // Secondary hash function salt.
    uint64_t tertiary [2]; // Tertiary hash function salt.
    BitVector *filter;
};

BloomFilter *bf_create(uint32_t size);

void bf_delete(BloomFilter **bf);

uint32_t bf_size(BloomFilter *bf);

void bf_insert(BloomFilter *bf, char *oldspeak);

bool bf_probe(BloomFilter *bf, char *oldspeak);

uint32_t bf_count(BloomFilter *bf);

void bf_print(BloomFilter *bf);


