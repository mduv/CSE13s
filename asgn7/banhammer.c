#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "bv.h"
#include "bf.h"
#include "bst.h"
#include "math.h"
#include "node.h"
#include "ht.h"

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

void test_bst_height() {
    // char *oldspeak = "window";
    // char *newspeak = "okno";
    // Node *root = bst_create();
    
    // root = bst_insert(root, "window", "okno");

    // root = bst_insert(root, "arm", "rook");

    // root = bst_insert(root, "wipe", "osoosh");
    // root = bst_insert(root, "zounds", NULL);
    // root = bst_insert(root, "annoy", "razdraz");
    // root = bst_insert(root, "bad", "baddiwad");



    // bst_print(root);

    // printf("height: %d\n", bst_height(root));
    // printf("size: %d\n", bst_size(root));

    // Node *f = bst_find(root, "wipe");
    // node_print(f);


    // HashTable *ht = ht_create(10);
    // ht_insert(ht, "arm", "rook");
}

void test_ht() {
    HashTable *ht = ht_create(1000);
    ht_insert(ht, "arm", "rook");
    ht_insert(ht, "window", "okno");
    ht_insert(ht, "wipe", "osoosh");
    ht_insert(ht, "zounds", NULL);
    ht_insert(ht, "annoy", "razdraz");
    ht_insert(ht, "bad", "baddiwad");
    printf("count: %d\n", ht_count(ht));
    printf("avg size: %f\n", ht_avg_bst_size(ht));
    printf("avg height: %f\n", ht_avg_bst_height(ht));

}

int main() {
    test_ht();
    return 1;
}
