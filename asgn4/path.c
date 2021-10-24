#include "path.h"

#include "stack.h"
#include "vertices.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct Path {
    Stack *vertices; // The vertices comprising the path
    uint32_t length; // The total length of the path
};

Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path));
    if (p) {
        p->vertices = stack_create(VERTICES);
        p->length = 0;
        if (!p->vertices) {
            free(p);
            p = NULL;
        }
    }
    return p;
}

void path_delete(Path **p) {
    stack_delete(&((*p)->vertices));
    free(*p);
    *p = NULL;
    return;
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    uint32_t y = 0;
    if (p == NULL || G == NULL || stack_full(p->vertices)) {
        return false;
    } else {
        if (!stack_empty(p->vertices)) {
            stack_peek(p->vertices, &y); // use peak to get last vertex
            p->length += graph_edge_weight(G, y, v); // add graph edge weight to plength
        } else {
            //p->length += graph_edge_weight(G, START_VERTEX, v);                      // add graph edge weight to plength
            p->length = 0;
        }
        return stack_push(p->vertices, v); // call stack_push and return if able to do it or not
    }
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    uint32_t x = 0;
    uint32_t y = 0;
    if (p == NULL || G == NULL || stack_empty(p->vertices)) {
        return false;
    } else {
        stack_pop(p->vertices, &x);
        stack_peek(p->vertices, &y); // use peak to get last vertex
        p->length -= graph_edge_weight(G, y, x);
        *v = x;
        return true;
    }
}

uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_length(Path *p) {
    return p->length;
}

void path_copy(Path *dst, Path *src) {
    stack_copy(dst->vertices, src->vertices);
    dst->length = src->length;
}

void path_print(Path *p, FILE *outfile, char *cities[]) {
    // call stack_print
    stack_print(p->vertices, outfile, cities);
}
