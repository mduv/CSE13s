#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include "node.h"
#include "math.h"


Node *bst_create(void) {
    Node* n = NULL;
    // n->left = NULL;
    // n->right = NULL;
    return n;
}

uint32_t bst_height(Node *root) {
    // Get the height of the tree
    if (!root) {
        return 0;
    } else {
        // Find the height of both subtrees
        // and use the larger one
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
   //printf("Visiting elements: ");
    if (root==NULL || root->oldspeak==oldspeak) { //if root->data is x then the element is found {
        return root;
    }
    if(root->oldspeak < oldspeak) { 
        return bst_find(root->left, oldspeak);
    } else { 
        return bst_find(root->right, oldspeak);
    }
}




Node *bst_insert(Node *root, char *oldspeak, char *newspeak) {

    // Return a new node if the tree is empty
    if (root == NULL) return node_create(oldspeak, newspeak);;

    // Traverse to the right place and insert the node
    if (oldspeak < root->oldspeak)
        root->left = bst_insert(root->left, oldspeak, newspeak);
    else
        root->right = bst_insert(root->right, oldspeak, newspeak);

    return root;
    // if(root==NULL) {
    //     return node_create(oldspeak, newspeak);
    // }
    // if (oldspeak < root->oldspeak){
    //     root->left = bst_insert(root->left, oldspeak, newspeak);
    // }
    // else if (oldspeak > root->oldspeak) { 
    //     // node_print(root);
    //     root->right = bst_insert(root->right, oldspeak, newspeak);
    // // node_print(root);
    // }
    // return root;

}

void bst_print(Node *root) {
    // node_print(root);
    // printf("hello\n");
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
    bst_delete(&(*root)->left);
    bst_delete(&(*root)->right);
    node_delete(root);
}

