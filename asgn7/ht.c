#include "ht.h"
#include "salts.h"
#include "node.h"

#include "speck.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>




struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    Node **trees;
};

/* The constructor for a hash table. The size parameter denotes the number of indices, or binary search
trees, that the hash table can index up to. The salt for the hash table is provided in salts.h. */

HashTable *ht_create(uint32_t size) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    if (ht == NULL) {
        return NULL;
    }
    ht->size = size;
    ht->salt[0] = SALT_HASHTABLE_LO;
    ht->salt[1] = SALT_HASHTABLE_HI;
    
    ht->trees = (Node **) malloc(sizeof(Node*) * size);
    if (ht->trees == NULL) {
        return NULL;
    }
    return ht;
}

/* The destructor for a hash table. Each of the binary search trees trees, the underlying array of binary
search tree root nodes, is freed. The pointer that was passed in should be set to NULL */
void ht_delete(HashTable **ht) {
    if (ht == NULL || *ht == NULL) {
        return;
    }

    uint32_t size = ht_size(*ht);
    for (uint32_t i = 0; i < size; i++) {
        bst_delete(&((*ht)->trees[i]));
    }
    free(*ht);
    *ht = NULL;
    return;
}

// Returns the hash table’s size.
uint32_t ht_size(HashTable *ht) {
    if (ht == NULL) {
        return 0;
    }
    return ht->size;
}


/* Searches for an entry, a node, in the hash table that contains oldspeak. A node stores oldspeak and
its newspeak translation. The index of the binary search tree to perform a look-up on is calculated by
hashing the oldspeak. If the node is found, the pointer to the node is returned. Else, a NULL pointer is
returned. */
Node *ht_lookup(HashTable *ht, char *oldspeak) {
    if (ht == NULL) {
        return NULL;
    }

    uint32_t index = hash(ht->salt, oldspeak);
    index = index % ht->size;
    if (bst_find(ht->trees[index], oldspeak) != NULL) {
        return bst_find(ht->trees[index], oldspeak);
    } else {
        return NULL;
    }
}

/* Inserts the specified oldspeak and its corresponding newspeak translation into the hash table. The
index of the binary search tree to insert into is calculated by hashing the oldspeak. */
void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    uint32_t index = hash(ht->salt, oldspeak);
    index = index % ht->size;
    ht->trees[index] = bst_insert(ht->trees[index], oldspeak, newspeak);
    // bst_print(ht->trees[index]);
}

// Returns the number of non-NULL binary search trees in the hash table.
uint32_t ht_count(HashTable *ht) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < ht->size; i++) {
        if (ht->trees[i] != NULL) {
            count++;
        }
    }
    return count;
}

/* Returns the average binary search tree size. This is computed as the sum of the sizes over all the binary
search trees divided by the number of non-NULL binary search trees in the hash table. You will need to
use bst_size(), presented in §7, to compute this. */

double ht_avg_bst_size(HashTable *ht) {
    uint32_t sum = 0;
    for (uint32_t i = 0; i < ht->size; i++) {
        sum += bst_size(ht->trees[i]);
    }
    double avg = (double) (sum / ht_count(ht));
    return avg;
}


/* Returns the average binary search tree size. This is computed as the sum of the heights over all the binary
search trees divided by the number of non-NULL binary search trees in the hash table. You will need to
use bst_height(), presented in §7, to compute this. */
double ht_avg_bst_height(HashTable *ht) {
    uint32_t sum = 0;
    for (uint32_t i = 0; i < ht->size; i++) {
        sum += bst_height(ht->trees[i]);
    }
    double avg = (double) (sum / ht_count(ht));
    return avg;
}

void ht_print(HashTable *ht) {
    for (uint32_t i = 0; i < ht->size; i++) {
        if (ht->trees[i] != NULL) {
            bst_print(ht->trees[i]);
        }
        
    }
}


