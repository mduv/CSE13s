#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"
#include "math.h"


// struct Node {
//     char *oldspeak;
//     char *newspeak;
//     Node *left;
//     Node *right;
// };


Node *node_create(char *oldspeak, char *newspeak) {
    Node *n = (Node *) malloc(sizeof(Node));
    if (n == NULL) {
        return NULL;
    }
    n->left = NULL;
    n->right = NULL;
    if (oldspeak == NULL) {
        n->oldspeak = NULL;
    } else {
        char* oldspeak_copy = strdup(oldspeak);
        n->oldspeak = oldspeak_copy;
    }
    // printf("oldspeak: %s\n", n->oldspeak);
    if (newspeak == NULL) {
        n->newspeak = NULL;
    } else {
        char* newspeak_copy = strdup(newspeak);
        n->newspeak = newspeak_copy;
    }
    // printf("newspeak: %s\n", n->newspeak);
    return n;
}

void node_delete(Node **n) {
    free((*n)->oldspeak);
    free((*n)->newspeak);
    free(*n); 
    *n = NULL; 
    return;
}

void node_print(Node *n) {
    if ((n->oldspeak != NULL) && (n->newspeak != NULL)) {
        printf("%s -> %s\n", n->oldspeak , n->newspeak);
    }
    else if ((n->oldspeak != NULL) && (n->newspeak == NULL)) {
        printf("%s\n", n->oldspeak);
    } else {
        printf("No node");
    }
}


