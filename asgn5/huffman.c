#include "io.h"
#include "code.h"
#include "defines.h"
#include "node.h"
#include "pq.h"


#include <stdint.h>
#include <unistd.h>
#include <stdio.h>


/* Constructs a Huffman tree given a computed histogram. The histogram will have ALPHABET indices,
one index for each possible symbol. Returns the root node of the constructed tree. The use of static
array indices in parameter declarations is a C99 addition. In this case, it informs the compiler that the
histogram hist should have at least ALPHABET number of indices. */

Node *build_tree(uint64_t hist[static ALPHABET]) {
    PriorityQueue *tree_queue = pq_create(ALPHABET); // empty pq of elements in hist
    for (int i = 0; i < ALPHABET; i++) {
        if (hist[i] > 0) {
            Node *element_node = node_create(i, hist[i]);
            enqueue(tree_queue, element_node);
        }
    }
    while (pq_size(tree_queue) > 1) {
        Node *left = 0;
        dequeue(tree_queue, &left);
        Node *right = 0;
        dequeue(tree_queue, &right); 
        Node *parent = node_join(left, right);
        enqueue(tree_queue, parent);
    }
    Node *root = 0;
    dequeue(tree_queue, &root);
    return root;
}
// void build_codes(Node *root, Code table[static ALPHABET]);

// void dump_tree(int outfile, Node *root);

// Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]);

// void delete_tree(Node **root);


