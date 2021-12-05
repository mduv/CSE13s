#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include "node.h"
#include "math.h"


Node *bst_create(void) {
    return NULL;
}

uint32_t bst_height(Node *root) {
    // Get the height of the tree
    if (!root) {
        return 0;
    } else {
        int left_height = bst_height(root->left);
        int right_height = bst_height(root->right);
        if (left_height >= right_height) {
            return left_height + 1;
        } else {
            return right_height + 1;
        }
    }
}


// Returns the size of the binary search tree rooted at root. The size of a tree is equivalent to the number of
// nodes in the tree.
uint32_t bst_size(Node *root) {
    if (root == NULL) {
        return 0;
    } else {
        return (bst_size(root->left) + 1 + bst_size(root->right));
    }  
}


/* Searches for a node containing oldspeak in the binary search tree rooted at root. If a node is found, the
pointer to the node is returned. Else, a NULL pointer is returned. */

Node *bst_find(Node *root, char *oldspeak) {
    
    // printf("iteration: %d\n", count);

    if (root==NULL || strcmp(root->oldspeak, oldspeak) == 0) { // if root->oldspeak is oldspeak then the element is found {
        return root;
    }
    if (strcmp(root->oldspeak, oldspeak) < 0) { 
        return bst_find(root->right, oldspeak);
    } else { 
        // printf("hello\n");
        return bst_find(root->left, oldspeak);
    }
    return NULL;
}




Node *bst_insert(Node *root, char *oldspeak, char *newspeak) {

    // Return a new node if the tree is empty
    if (root == NULL) { 
        // node_print(root);
        return node_create(oldspeak, newspeak);
    }
    // Traverse to the right place and insert the node

    if (strcmp(oldspeak, root->oldspeak) == 0) {
        // don't insert duplicates
        return root;
    }
    if (strcmp(oldspeak, root->oldspeak) < 0) {     // oldspeak is < root->oldspeak
        root->left = bst_insert(root->left, oldspeak, newspeak);
        return root;
    } else {
        root->right = bst_insert(root->right, oldspeak, newspeak);
        return root;
    }
    return root;

}

void bst_print(Node *root) {
    if (root != NULL) {
        bst_print(root->left);
        node_print(root);
        bst_print(root->right);
    } else {
        return;
    }
}

void bst_delete(Node **root) {
    if (root == NULL) {
        return;
    }
    bst_delete(&((*root)->left));
    bst_delete(&((*root)->right));
    node_delete(root);
}

