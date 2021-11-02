#include "pq.h"
#include "node.h"
#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

struct PriorityQueue {
    uint32_t head;      // head of the priority queue
    uint32_t tail;      // tail of the priority queue
    uint32_t size;      // size of the priority queue
    uint32_t capacity;  // capacity of the priority queue
    Node **items;       // an array of nodes
};

// The constructor for a priority queue. The priority queue’s maximum capacity is specified by capacity.
PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));                
    if (q) {
        q->head = 0;
        q->tail = 0;
        q->size = 0;
        q->capacity = capacity;
        q->items = (Node **) malloc(capacity * sizeof(Node *));
    }
    return q;
}

// The destructor for a priority queue.
void pq_delete(PriorityQueue **q) {
    if (*q && (*q)->items) {
        free((*q)->items);
        free(*q);
        *q = NULL; // Set the pointer to NULL after freeing the memory for a priority queue.
    }
    return;
}

// Returns true if the priority queue is empty and false otherwise.
bool pq_empty(PriorityQueue *q) {
    if (q->size == 0) {
        return true;
    } else {
        return false;
    }
}

// Returns true if the priority queue is full and false otherwise.
bool pq_full(PriorityQueue *q) {
    if (q->size == q->capacity) {
        return true;
    } else {
        return false;
    }
}

// Returns the number of items currently in the priority queue.
uint32_t pq_size(PriorityQueue *q) {
    return q->size;
}

// Enqueues a node into the priority queue. Returns false if the priority queue is full prior to enqueuing the node and true otherwise to indicate the successful enqueuing of the node.
// bool enqueue(PriorityQueue *q, Node *n) {
//     if (pq_full(q)) {
//         return false;
//     } else {
//         return true;
//     }
// }

/* Dequeues a node from the priority queue, passing it back through the double pointer n. The node de-
queued should have the highest priority over all the nodes in the priority queue. Returns false if the
priority queue is empty prior to dequeuing a node and true otherwise to indicate the successful de-
queuing of a node. */
bool dequeue(PriorityQueue *q, Node **n) {
    if (pq_empty(q)) {
        return false;
    } else {
        *n = q->items[q->head++];
        q->size--;
        return true;
    }
}

// void pq_print(PriorityQueue *q);


