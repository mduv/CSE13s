#include "bf.h"
#include "bv.h"
#include "salts.h"
#include "speck.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>


struct BloomFilter {
    uint64_t primary [2]; // Primary hash function salt.
    uint64_t secondary [2]; // Secondary hash function salt.
    uint64_t tertiary [2]; // Tertiary hash function salt.
    BitVector *filter;
};


/* The constructor for a Bloom filter. The primary, secondary, and tertiary salts that should be used are
provided in salts.h. Note that you will also have to implement the bit vector ADT for your Bloom filter,
as it will serve as the array of bits necessary for a proper Bloom filter. */

BloomFilter *bf_create(uint32_t size) {

    BloomFilter* bf = (BloomFilter*)malloc(sizeof(BloomFilter));

    if (bf == NULL) {
        return NULL;
    }

    bf->primary[0] = SALT_PRIMARY_LO;
    bf->primary[1] = SALT_PRIMARY_HI;

    bf->secondary[0] = SALT_SECONDARY_LO;
    bf->secondary[1] = SALT_SECONDARY_HI;


    bf->tertiary[0] = SALT_TERTIARY_LO;
    bf->tertiary[1] = SALT_TERTIARY_HI;

    bf->filter = bv_create(size);

    return bf;
}

/* The destructor for a Bloom filter. As with all other destructors, it should free any memory allocated by
the constructor and null out the pointer that was passed in. */

void bf_delete(BloomFilter **bf) {    
    bv_delete(&((*bf)->filter));
    free(*bf);
    *bf = NULL;
    return;
}

/* Returns the size of the Bloom filter. In other words, the number of bits that the Bloom filter can access.
Hint: this is the length of the underlying bit vector. */

uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter);
}

/* Takes oldspeak and inserts it into the Bloom filter. This entails hashing oldspeak with each of the three
salts for three indices, and setting the bits at those indices in the underlying bit vector. */

void bf_insert(BloomFilter *bf, char *oldspeak) {
    uint32_t size = bf_size(bf);
    uint32_t index_p = hash(bf->primary, oldspeak);
    index_p = index_p % size;
    // printf("p hash: %d\n", index_p);
    uint32_t index_s = hash(bf->secondary, oldspeak);
    index_s = index_s % size;
    // printf("s hash: %d\n", index_s);
    uint32_t index_t = hash(bf->tertiary, oldspeak);
    index_t = index_t % size;
    // printf("t hash: %d\n", index_t);


    bv_set_bit(bf->filter, index_p);
    bv_set_bit(bf->filter, index_s);
    bv_set_bit(bf->filter, index_t);

    // printf("p bit set?: %d\n", bv_get_bit(bf->filter, index_p));
    // printf("s bit set?: %d\n", bv_get_bit(bf->filter, index_s));
    // printf("t bit set?: %d\n", bv_get_bit(bf->filter, index_t));

}


/* Probes the Bloom filter for oldspeak. Like with bf_insert(), oldspeak is hashed with each of the three
salts for three indices. If all the bits at those indices are set, return true to signify that oldspeak was most
likely added to the Bloom filter. Else, return false. */

bool bf_probe(BloomFilter *bf, char *oldspeak) {
    uint32_t size = bf_size(bf);
    uint32_t index_p = hash(bf->primary, oldspeak);
    index_p = index_p % size;
    uint32_t index_s = hash(bf->secondary, oldspeak);
    index_s = index_s % size;
    uint32_t index_t = hash(bf->tertiary, oldspeak);
    index_t = index_t % size;

    if (bv_get_bit(bf->filter, index_p) && bv_get_bit(bf->filter, index_s) && bv_get_bit(bf->filter, index_t)) {
        return true;
    } else {
        return false;
    }
}

// Returns the number of set bits in the Bloom filter.
uint32_t bf_count(BloomFilter *bf) {
    uint32_t count = 0;
    uint32_t size = bf_size(bf);
    for (uint32_t i = 0; i < size; i++) {
        if (bv_get_bit(bf->filter, i)) {
            count++;
        }
    }
    return count;
}

void bf_print(BloomFilter *bf) {
    bv_print(bf->filter);
}


