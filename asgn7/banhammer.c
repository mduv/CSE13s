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

int myPow(int x,int n)
{
    int i; /* Variable used in loop counter */
    int number = 1;

    for (i = 0; i < n; ++i)
        number *= x;

    return(number);
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
            return 0;
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
    
    /* Initialize your Bloom filter and hash table. */
    BloomFilter *bf = bf_create(filter_size);
    
    HashTable *ht = ht_create(table_size);

    /* Read in a list of badspeak words with fscanf(). Again, badspeak is simply oldspeak without a
    newspeak translation. Badspeak is strictly forbidden. Each badspeak word should be added to the
    Bloom filter and the hash table. The list of proscribed words will be in badspeak.txt, which can
    be found in the resources repository. */
    FILE *bs_p = fopen("badspeak.txt", "r");
    if (bs_p == NULL) {
        bf_delete(&bf);
        ht_delete(&ht);
        return -1;
    }
    struct stat sb;
    struct stat vb;
    stat("badspeak.txt", &sb);
    char *bs_contents = malloc(sb.st_size);
    if (bs_contents == NULL) {
        return -1;
    }

    while (fscanf(bs_p, "%s\n", bs_contents) != EOF) {
        bf_insert(bf, bs_contents);
        ht_insert(ht, bs_contents, NULL);
    }

    /* Read in a list of oldspeak and newspeak pairs with fscanf(). Only the oldspeak should be added to
    the Bloom filter. The oldspeak and newspeak are added to the hash table. The list of oldspeak and
    newspeak pairs will be in newspeak.txt, which can also be found in the resources repository. */

    FILE *os_ns_p = fopen("newspeak.txt", "r");
    if (os_ns_p == NULL) {
        fclose(bs_p);
        bf_delete(&bf);
        ht_delete(&ht);
        free(bs_contents);
        return -1;
    }
    stat("newspeak.txt", &vb);
    char *os_contents = malloc(sb.st_size);
    char *ns_contents = malloc(vb.st_size);
    if (os_contents == NULL || ns_contents == NULL) {
        return -1;
    }

    while (fscanf(os_ns_p, "%s %s\n", os_contents, ns_contents) != EOF) {
        bf_insert(bf, os_contents);
        ht_insert(ht, os_contents, ns_contents);
    }

    /* Now that the lexicon of badspeak and oldspeak/newspeak translations has been populated, you
c   an start to filter out words. Read words in from stdin using the supplied parsing module. */
    #define WORD "[a-zA-Z0-9_'-]+"
    regex_t re;
    if (regcomp (&re , WORD , REG_EXTENDED)) {
        fprintf(stderr , "Failed to compile regex.\n");
    }

    char *word = NULL;

    bool thoughtcrime = false;
    bool rightspeak = false;

    HashTable *badspeak_ht = ht_create(bf_count(bf));
    HashTable *oldspeak_ht = ht_create(bf_count(bf));

    Node* badspeak_nodes[100000];
    Node* oldspeak_nodes[100000];
    int bsn = 0;
    int osn = 0;

    Node* badspeak_bst = bst_create();
    Node* oldspeak_bst = bst_create();


    while ((word = next_word(stdin , &re)) != NULL) {
        if (bf_probe(bf, word)) {
            Node *check = ht_lookup(ht, word);
            if (check != NULL) {
                // thoughtcrime
                if (check->newspeak == NULL) {
                    ht_insert(badspeak_ht, word, NULL);
                    thoughtcrime = true;
                    badspeak_nodes[bsn++] = node_create(word, NULL);
                    badspeak_bst = bst_insert(badspeak_bst, word, NULL);
                } else {
                // Rightspeak
                    ht_insert(oldspeak_ht, word, check->newspeak);
                    rightspeak = true;
                    oldspeak_nodes[osn++] = node_create(word, check->newspeak);
                    oldspeak_bst = bst_insert(oldspeak_bst, word, check->newspeak);
                }
            }
        }
    }

    avg_bst_size = ht_avg_bst_size(ht);
    avg_bst_height = ht_avg_bst_height(ht);


    avg_branch_trav = (float) branches/ (float) lookups;
    ht_load = 100.0 * ( (float) ht_count(ht)/ (float) ht_size(ht));
    bf_load = 100.0 * ( (float) bf_count(bf)/ (float) bf_size(bf));


    if (statistics_mode) {
        printf("Average BST size: %f\n", avg_bst_size);
        printf("Average BST height: %f\n", avg_bst_height);
        printf("Average branches traversed: %f\n", avg_branch_trav);
        printf("Hash table load: %0.6f%%\n", ht_load);
        printf("Bloom filter load: %0.6f%%\n", bf_load);
        fclose(os_ns_p);
        fclose(bs_p);
        free(bs_contents);
        free(os_contents);
        free(ns_contents);
        bf_delete(&bf);
        ht_delete(&ht);
        ht_delete(&badspeak_ht);
        ht_delete(&oldspeak_ht);
        clear_words();
        regfree (&re);
        for (int i = 0; i < bsn; i++) {
            node_delete(&badspeak_nodes[i]);
        }
        for (int i = 0; i < osn; i++) {
            node_delete(&oldspeak_nodes[i]);
        }
        bst_delete(&badspeak_bst);
        bst_delete(&oldspeak_bst);
        
        return 0;
    } 

    if (thoughtcrime && !rightspeak) {
        printf("%s", badspeak_message);
        //ht_print(badspeak_ht);
        // for (int i = 0; i < bsn; i++) {
        //     node_print(badspeak_nodes[i]);
        // }
        bst_print(badspeak_bst);
    }

    if (!thoughtcrime && rightspeak) {
        printf("%s", goodspeak_message);
        //ht_print(oldspeak_ht);
        // for (int i = 0; i < osn; i++) {
        //     node_print(oldspeak_nodes[i]);
        // }
        bst_print(oldspeak_bst);
    }
    
    if (thoughtcrime && rightspeak) {
        printf("%s", mixspeak_message);
        //ht_print(badspeak_ht);
        //ht_print(oldspeak_ht);
        // for (int i = 0; i < bsn; i++) {
        //     node_print(badspeak_nodes[i]);
        // }
        // for (int i = 0; i < osn; i++) {
        //     node_print(oldspeak_nodes[i]);
        // }
        bst_print(badspeak_bst);
        bst_print(oldspeak_bst);
    }

    clear_words();
    regfree (&re);

    fclose(os_ns_p);
    fclose(bs_p);
    free(bs_contents);
    free(os_contents);
    free(ns_contents);
    bf_delete(&bf);
    ht_delete(&ht);
    ht_delete(&badspeak_ht);
    ht_delete(&oldspeak_ht);
    for (int i = 0; i < bsn; i++) {
        node_delete(&badspeak_nodes[i]);
    }
    for (int i = 0; i < osn; i++) {
        node_delete(&oldspeak_nodes[i]);
    }
    bst_delete(&badspeak_bst);
    bst_delete(&oldspeak_bst);

    return 0;
}

