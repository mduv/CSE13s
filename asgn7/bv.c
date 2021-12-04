#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "bv.h"
#include "math.h"

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

/* The constructor for a bit vector that holds length bits. In the even that sufficient memory cannot be al-
located, the function must return NULL. Else, it must return a BitVector *), or a pointer to an allocated
BitVector. Each bit of the bit vector should be initialized to 0. */

BitVector *bv_create(uint32_t length) {
    BitVector *bv = (BitVector *) malloc(sizeof(BitVector));
    if (bv == NULL) {
        return NULL;
    }
    bv->length = length;
    uint32_t arraysize = ceil(length / 8.0);
    bv->vector = (uint8_t *) calloc(arraysize, sizeof(uint8_t));
    if (bv->vector == NULL) {
        return NULL;
    }
    return bv;
}

/* The destructor for a bit vector. Remember to set the pointer to NULL after the memory associated with
the bit vector is freed. */
void bv_delete(BitVector **bv) {
    free((*bv)->vector);
    (*bv)->vector = NULL;
    free(*bv);
    *bv = NULL;
    return;
}

// Returns the length of a bit vector.
uint32_t bv_length(BitVector *bv) {
    // printf("length: %d\n", bv->length);
    if (bv == NULL) {
        return -1;
    }
    return bv->length;
}

/* Sets the i th bit in a bit vector. If i is out of range, return false. Otherwise, return true to indicate
success. */
bool bv_set_bit(BitVector *bv, uint32_t i) {
    uint32_t k = i / 8; // index of the element in the unit8 array
    uint32_t pos = i % 8; // bit position in uint8 bit
    uint8_t flag = 1; // 00...1

    if (i >= bv->length) {
        return false;
    } else {
        flag = flag << pos;
        bv->vector[k] = bv->vector[k] | flag;
        // printf("set bit: %x\n", flag);
        return true;
    }
}

bool bv_clr_bit(BitVector *bv, uint32_t i) {
    uint32_t k = i / 8; // index of the element in the unit8 array
    uint32_t pos = i % 8; // bit position in uint8 bit
    uint8_t flag = 1; // 00...0
    if (i >= bv->length) {
        return false;
    } else {
        flag = flag << pos;
        flag = ~flag;
        bv->vector[k] = bv->vector[k] & flag;
        ;
        // printf("clr bit: %x\n", bv->vector[k]);
        return true;
    }
}

bool bv_get_bit(BitVector *bv, uint32_t i) {
    uint32_t k = i / 8; // index of which byte
    uint32_t pos = i % 8; // bit position in uint8 bit
    uint8_t flag = 1;
    flag = flag << pos;
    if (i > bv->length) {
        return false;
    }
    if ((bv->vector[k] & flag) == flag) {
        return true;
    } else {
        return false;
    }
}

void bv_print(BitVector *bv) {
    printf("\nprint bitvector: ");
    for (uint32_t i = 0; i < bv->length; i++) {
        printf("%d", bv_get_bit(bv, i));
    }
    printf("\n");
}
