#include "node.h"
#include "code.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// The constructor for a node. Sets the node’s symbol as symbol and its frequency as frequency.
Node *node_create(uint8_t symbol, uint64_t frequency) {     
    Node *n = (Node *) malloc(sizeof(Node));                
    if (n) {
        if (n->left == NULL && n->right == NULL ) {     // make sure left and right pointers are NULL
            n->symbol = symbol;                         // sets the node’s symbol as symbol
            n->frequency = frequency;                   // sets the node’s frequency as frequency
        }
    }
    return n;
}

// The destructor for a node.
void node_delete(Node **n) {
    free(*n);                                           // free memory for a node
    *n = NULL;                                          // set pointer to NULL
    return;
}

/*  Joins a left child node and right child node, returning a pointer to a created parent node. The parent
    node’s left child will be left and its right child will be right. The parent node’s symbol will be ‘$’ and
    its frequency the sum of its left child’s frequency and its right child’s frequency. */
Node *node_join(Node *left, Node *right) {
    uint64_t parent_frequency = left->frequency + right->frequency;  // parent node's frequency is the sum of its left child's frequency and its right child's frequency
    Node *parent_node = node_create('$', parent_frequency); // creates parent node with symbol '$' and frequency: parent_frequency
    parent_node->left = left;                               // parent node's left child will be left
    parent_node->right = right;                             // parent node's right child will be right
    return parent_node;

}

// A debug function to verify that your nodes are created and joined correctly.
void node_print(Node *n) {
    
    if (n->left == NULL && n->right == NULL) {
        // print symbol
        printf("No children\n");
        printf("Symbol: %" PRIx8 "\n", n->symbol);
        // print the frequency PRIu64
        printf("Frequency: %" PRIu64 "\n", n->frequency);
    } else {
        // print symbol and freq of the children
        printf("Symbol of left: %" PRIx8 "\n", n->left->symbol);
        printf("Frequency of left: %" PRIu64 "\n", n->left->frequency);
        printf("Symbol of right: %" PRIx8 "\n", n->right->symbol);
        printf("Frequency of right: %" PRIu64 "\n", n->right->frequency);
    }
   
}


