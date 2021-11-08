#include "node.h"
#include "stack.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct Stack {
    uint32_t top; // top of the stack
    uint32_t capacity; // capacity of the stack
    Node **items; // an array of nodes
};

// The constructor for a stack. The maximum number of nodes the stack can hold is specified by capacity.
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (Node **) calloc(capacity, sizeof(Node *));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

// The destructor for a stack.
void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL; // set the pointer to NULL after freeing the memory allocated by the stack.
    }
    return;
}

// Returns true if the stack is empty and false otherwise.
bool stack_empty(Stack *s) {
    if (stack_size(s) == 0) {
        return true;
    } else {
        return false;
    }
}

// Returns true if the stack is full and false otherwise.
bool stack_full(Stack *s) {
    if (stack_size(s) == s->capacity) {
        return true;
    } else {
        return false;
    }
}

// Returns the number of nodes in the stack.
uint32_t stack_size(Stack *s) {
    return s->top;
}

// Pushes a node onto the stack.
// Returns false if the stack is full prior to pushing the node and true otherwise to indicate the successful pushing of a node.
bool stack_push(Stack *s, Node *n) {
    if (s == NULL || stack_full(s)) {
        return false;
    } else {
        s->items[s->top] = n;
        s->top += 1;
        return true;
    }
}

// Pops a node off the stack, passing it back through the double pointer n.
// Returns false if the stack is empty prior to popping a node and true otherwise to indicate the succesuccessful popping of a node.
bool stack_pop(Stack *s, Node **n) {
    if (stack_empty(s)) {
        return false;
    } else {
        *n = s->items[s->top - 1];
        s->top -= 1;
        return true;
    }
}

// debug function
// void stack_print(Stack *s) {
//     for (uint32_t i = 0; i < s->top; i += 1) {
// }
