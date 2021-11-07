#include "io.h"
#include "code.h"
#include "defines.h"
#include "node.h"
#include "pq.h"
#include "stack.h"


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

Code c;
int i = 0;
void build_codes(Node *root, Code table[static ALPHABET]) {
    if (i==0) {
        c = code_init();
    }
    i++;

    if (root != NULL) {
        if (root->left == NULL && root->right == NULL) {
            // leaf node
            table[root->symbol] = c;
        } else {
            code_push_bit(&c, 0);
            build_codes(root->left, table);
            uint8_t x = 0;
            code_pop_bit(&c, &x);

            code_push_bit(&c, 1);
            build_codes(root->right, table);
            code_pop_bit(&c, &x);
        }
    }
}

void dump_tree(int outfile, Node *root) {
    if (root != NULL) {
        dump_tree(outfile, root->left);
        dump_tree(outfile, root->right);

        if (root->left == NULL && root->right == NULL) {
            // leaf node
            uint8_t l = 'L';
            write_bytes(outfile, &l, sizeof(l));
            uint8_t symbol = root->symbol;
            write_bytes(outfile, &symbol, sizeof(symbol));
        } else {
            // interior node
            uint8_t i = 'I';
            write_bytes(outfile, &i, sizeof(i));
        }
    }
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {
    Stack *s_nodes = stack_create(nbytes);

    for (int16_t i = 0; i < nbytes; i++) {
        if (tree[i] == 'L') {
            // leaf
            Node *next = node_create(tree[i+1], 0);
            stack_push(s_nodes, next);
        }
        if (tree[i] == 'I') {
            // interior
            Node *right = 0;
            stack_pop(s_nodes, &right);

            Node *left = 0;
            stack_pop(s_nodes, &left);

            Node *parent = node_join(left, right);
            stack_push(s_nodes, parent);
        }
    }
    Node *root = 0;
    stack_pop(s_nodes, &root);
    return root;
}

void delete_tree(Node **root) {
    if (root != NULL) {
        Node *nodePtr = *root;
        if (nodePtr != NULL) {
            delete_tree(&(nodePtr->left));
            delete_tree(&(nodePtr->right));
            node_delete(&nodePtr);
        }
    }
}


