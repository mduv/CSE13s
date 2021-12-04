#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "bv.h"
#include "bf.h"
#include "math.h"
#include "node.h"


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

void test_bf() {
    char *oldspeak = "Stupid";
    uint32_t size = 10;
    BloomFilter* bfilt = bf_create(size);
    bf_insert(bfilt, oldspeak);
    bool probe = bf_probe(bfilt, oldspeak);
    uint32_t count = bf_count(bfilt);
    printf("probe: %d, count: %d\n", probe, count);
    bf_print(bfilt);
}

void test_node() {
    char *oldspeak = "stupid";
    char *newspeak = "hey";
    Node *n = node_create(oldspeak, newspeak);
    node_print(n);
}

int main() {
    // test_bv_length();
    // test_bv_set_bit();
    test_node();
    return 1;
}



