#include "code.h"
#include "defines.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* This function will not require any dynamic memory allocation. You will simply create a new Code on
the stack, setting top to 0, and zeroing out the array of bits, bits. The initialized Code is then returned. */
Code code_init(void) {
    Code c = {.top = 0, .bits = {0}};
    return c;
}

// Returns the size of the Code, which is exactly the number of bits pushed onto the Code.
uint32_t code_size(Code *c) {
    return c->top;
}

// Returns true if the Code is empty and false otherwise.
bool code_empty(Code *c) {
    if (c->top == 0) {
        return true;
    } else {
        return false;
    }
}

// Returns true if the Code is full and false otherwise. 
bool code_full(Code *c) {
    if (c->top == ALPHABET) { // The maximum length of a code in bits is 256, which we have defined using the macro ALPHABET.
        return true;
    } else {
        return false;
    }
}

// Sets the bit at index i in the Code, setting it to 1. If i is out of range, return false. Otherwise, return true to indicate success.
bool code_set_bit(Code *c, uint32_t i) {
    if (i > ALPHABET) {
        return false;
    } else {
        c->bits[i / 8] = 1;
        return true;
    }
}

// Clears the bit at index i in the Code, clearing it to 0. If i is out of range, return false. Otherwise, return true to indicate success.
bool code_clr_bit(Code *c, uint32_t i) {
    if (i > ALPHABET) {
        return false;
    } else {
        c->bits[i / 8] = 0;
        return true;
    }
}

// Gets the bit at index i in the Code. If i is out of range, or if bit i is equal to 0, return false. Return true if and only if bit i is equal to 1.
bool code_get_bit(Code *c, uint32_t i) {
    if (i > ALPHABET || c->bits[i / 8] == 0) {
        return false;
    }
    if (c->bits[i / 8] == 1) {
        return true;
    } else {
        return false;
    }
}

// Pushes a bit onto the Code. The value of the bit to push is given by bit. Returns false if the Code is full prior to pushing a bit and true otherwise to indicate the successful pushing of a bit.
bool code_push_bit(Code *c, uint8_t bit) {
    if (code_full(c)) {
        return false;
    } else {
        c->bits[c->top] = bit;
        c->top += 1;
        return true;
    }

}

// Pops a bit off the Code. The value of the popped bit is passed back with the pointer bit. Returns false if the Code is empty prior to popping a bit and true otherwise to indicate the successful popping of a bit.
bool code_pop_bit(Code *c, uint8_t *bit) {
    if (code_empty(c)) {
        return false;
    }
    else {
        *bit = c->bits[c->top-1];
        c->top -= 1;
        return true;
    }
}

// for debugging
void code_print(Code *c) {
    for (uint32_t i = 0; i < c->top; i += 1) {
        printf("bit array value: %" PRIu32 "\n", c->bits[i]);
    }
}


