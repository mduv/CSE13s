#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "bv.h"
#include "math.h"

void test_bv_set_bit() {
    uint32_t length = 100;
    BitVector *bitv = bv_create(length);
    bv_set_bit(bitv, 18);
    bool returned_bit = bv_get_bit(bitv, 18);
    if (returned_bit != 1) {
        printf("Set bit didnt work\n");
    }
    bv_print(bitv);
}

void test_bv_length() {
    uint32_t length = 100;
    BitVector *bitv = bv_create(length);
    uint32_t returned_length = bv_length(bitv);
    if (returned_length != length) {
        printf("Lengths don't match\n");
    }
}

int main() {
    test_bv_length();
    test_bv_set_bit();
    return 1;
}
