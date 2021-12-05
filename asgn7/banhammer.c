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
#include <regex.h>
#include "parser.h"
#include "messages.h"

#define OPTIONS "sht:f:"

bool statistics_mode = false;
// static FILE *input = NULL;


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
    // input = stdin;
    double avg_bst_size = 0.0;
    double avg_bst_height = 0.0;
    double avg_branch_trav = 0.0;
    double ht_load = 0.0;
    double bf_load = 0.0;

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
        case 't':
            table_size = atoi(optarg);
            break;
        case 'f':
            filter_size = atoi(optarg);
            break;
        case 's':
            statistics_mode = true;
            break;

        }
    }

    // printf("table size: %d\n", table_size);
    // printf("filter size: %d\n", filter_size);
    
    /* Initialize your Bloom filter and hash table. */
    BloomFilter *bf = bf_create(filter_size);
    
    HashTable *ht = ht_create(table_size);

    /* Read in a list of badspeak words with fscanf(). Again, badspeak is simply oldspeak without a
    newspeak translation. Badspeak is strictly forbidden. Each badspeak word should be added to the
    Bloom filter and the hash table. The list of proscribed words will be in badspeak.txt, which can
    be found in the resources repository. */
    FILE *bs_p = fopen("badspeak.txt", "r");
    struct stat sb;
    struct stat vb;
    stat("badspeak.txt", &sb);
    char *bs_contents = malloc(sb.st_size);

    while (fscanf(bs_p, "%[^\n] ", bs_contents) != EOF) {
        bf_insert(bf, bs_contents);
        ht_insert(ht, bs_contents, NULL);
    }
    // printf("bf count: %d\n", bf_count(bf));

    /* Read in a list of oldspeak and newspeak pairs with fscanf(). Only the oldspeak should be added to
    the Bloom filter. The oldspeak and newspeak are added to the hash table. The list of oldspeak and
    newspeak pairs will be in newspeak.txt, which can also be found in the resources repository. */

    FILE *os_ns_p = fopen("newspeak.txt", "r");
    stat("newspeak.txt", &vb);
    char *os_contents = malloc(sb.st_size);
    char *ns_contents = malloc(vb.st_size);

    while (fscanf(os_ns_p, "%s %s", os_contents, ns_contents) != EOF) {
        bf_insert(bf, os_contents);
        ht_insert(ht, os_contents, ns_contents);
    }

    /* Now that the lexicon of badspeak and oldspeak/newspeak translations has been populated, you
c   an start to filter out words. Read words in from stdin using the supplied parsing module. */
    #define WORD "[a-zA-Z]+"
    regex_t re;
    if (regcomp (&re , WORD , REG_EXTENDED)) {
        fprintf(stderr , "Failed to compile regex.\n");
    }

    char *word = NULL;

    bool thoughtcrime = false;
    bool rightspeak = false;

    HashTable *badspeak_ht = ht_create(bf_count(bf));
    HashTable *oldspeak_ht = ht_create(bf_count(bf));

    while ((word = next_word(stdin , &re)) != NULL) {
        if (bf_probe(bf, word)) {
            Node *check = ht_lookup(ht, word);
            // node_print(check);
            if (check != NULL) {
                // thoughtcrime
                if (check->newspeak == NULL) {
                    ht_insert(badspeak_ht, word, NULL);
                    thoughtcrime = true;
                } else {
                // Rightspeak
                    ht_insert(oldspeak_ht, word, check->newspeak);
                    rightspeak = true;
                }
            }
        }
        // printf("Word: %s\n", word);
    }
    // printf("thoughtcrime: %d, rightspeak: %d\n", thoughtcrime, rightspeak);

    avg_bst_size = ht_avg_bst_size(ht);
    avg_bst_height = ht_avg_bst_height(ht);
    // printf("branches: %llu\n", branches);
    // printf("lookups: %llu\n", lookups);

    avg_branch_trav = (float) branches/ (float) lookups;
    ht_load = 100.0 * ( (float) ht_count(ht)/ (float) ht_size(ht));
    bf_load = 100.0 * ( (float) bf_count(bf)/ (float) bf_size(bf));


    if (statistics_mode) {
        printf("Average BST size: %f\n", avg_bst_size);
        printf("Average BST height: %f\n", avg_bst_height);
        printf("Average branches traversed: %f\n", avg_branch_trav);
        printf("Hash table load: %0.6f%%\n", ht_load);
        printf("Bloom filter load: %0.6f%%\n", bf_load);
        return 0;
    } 

    if (thoughtcrime && !rightspeak) {
        printf("%s", badspeak_message);
        ht_print(badspeak_ht);
    }

    if (!thoughtcrime && rightspeak) {
        printf("%s", goodspeak_message);
        ht_print(oldspeak_ht);
    }
    
    if (thoughtcrime && rightspeak) {
        printf("%s", mixspeak_message);
        ht_print(badspeak_ht);
        ht_print(oldspeak_ht);
    }

    clear_words();
    regfree (&re);


    // printf("bf count: %d\n", bf_count(bf));
    //ht_delete(&ht);
    
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
