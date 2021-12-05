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
#include <unistd.h>
#include <inttypes.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define OPTIONS "sht:f:"

bool statistics_mode = false;

int myPow(int x,int n)
{
    int i; /* Variable used in loop counter */
    int number = 1;

    for (i = 0; i < n; ++i)
        number *= x;

    return(number);
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
    // printf("avg size: %f\n", ht_avg_bst_size(ht));
    // printf("avg height: %f\n", ht_avg_bst_height(ht));

    ht_print(ht);
    printf("#############\n");
    Node *l = ht_lookup(ht, "bad");
    node_print(l);
}

int main(int argc, char **argv) {
    int opt = 0;
    optind = 1;

    int table_size = myPow(2,16);
    int filter_size = myPow(2,20);

    // Parse command-line options using getopt() and handle them accordingly.


    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf("SYNOPSIS\n\tA word filtering program for the GPRSC.\n\tFilters out and reports bad words parsed from stdin."
                   "\n\nUSAGE\n\t./banhammer [-hs] [-t size] [-f size]"
                   "n\nOPTIONS"
                   "\n\t-h              Program usage and help."
                   "\n\t-s              Print program statistics."
                   "\n\t-t size         Specify hash table size (default: 2^16)."
                   "\n\t-f size         Specify Bloom filter size (default: 2^20).\n");
            break;
        case 's':
            statistics_mode = true;
            break;
        case 't':
            table_size = atoi(optarg);
            break;
        case 'f':
            filter_size = atoi(optarg);
            break;
        }
    }

    // printf("table size: %d\n", table_size);
    // printf("filter size: %d\n", filter_size);
    
    /* Initialize your Bloom filter and hash table. */
    BloomFilter *bf = bf_create(filter_size);
    
    // HashTable *ht = ht_create(table_size);

    /* Read in a list of badspeak words with fscanf(). Again, badspeak is simply oldspeak without a
    newspeak translation. Badspeak is strictly forbidden. Each badspeak word should be added to the
    Bloom filter and the hash table. The list of proscribed words will be in badspeak.txt, which can
    be found in the resources repository. */
    FILE *fp = fopen("badspeak.txt", "r");
    struct stat sb;
    stat("badspeak.txt", &sb);
    char *file_contents = malloc(sb.st_size);

    while (fscanf(fp, "%[^\n] ", file_contents) != EOF) {
        bf_insert(bf, file_contents);
        // ht_insert(ht, file_contents, NULL);
    }



    // printf("bf count: %d\n", bf_count(bf));
    test_ht();
    return 1;
}

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


// int main() {
//     test_ht();
//     return 1;
// }
