#include "graph.h"
#include "vertices.h"
#include <inttypes.h>


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct Graph {
    uint32_t vertices;                      // Number of vertics
    bool undirected;                        // Undirected Graph?
    bool visited[VERTICES];                 // Where have we gone?
    uint32_t matrix[VERTICES][VERTICES];    // Adjaceny Matrix
};

bool verticesWithinBounds(uint32_t v) {
    if ((START_VERTEX <= v && v <= VERTICES)) {
        return true;
    }
    else {
        return false;
    }
}



Graph *graph_create(uint32_t vertices, bool undirected) {
	Graph *G = (Graph *)calloc(1, sizeof(Graph));
    if (G) {
        G->vertices = vertices;
	    G->undirected = undirected;
    }
	return G;
}

void graph_delete(Graph **G) {
    free(*G);
    *G = NULL;
    return;
}

uint32_t graph_vertices(Graph *G) {
    return G->vertices;
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    if ((verticesWithinBounds(i) && verticesWithinBounds(j))) {
        G->matrix[i][j] = k;
        if (G->undirected) {
            G->matrix[j][i] = k;
        }
        return true;
    }
    else {
        return false;
    }
}

bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if ((verticesWithinBounds(i) && verticesWithinBounds(j)) && (G->matrix[i][j] > 0)) {
        return true;
    }
    else {
        return false;
    }

}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if (graph_has_edge(G, i, j)) {
        return G->matrix[i][j];
    }
    else {
        return false;
    }
}

bool graph_visited(Graph *G, uint32_t v) {
    if (G->visited[v]) {
        return true;
    }
    else {
        return false;
    }
}

void graph_mark_visited(Graph *G, uint32_t v) {
    if (verticesWithinBounds(v)) {
        G->visited[v] = true;
    }
}

void graph_mark_unvisited(Graph *G, uint32_t v) {
    if (verticesWithinBounds(v)) {
        G->visited[v] = false;
    }
}

void graph_print(Graph *G) {
    for (uint32_t i = 0; i < G->vertices; i += 1) {
        for (uint32_t j = 0; j < G->vertices; j += 1) {
            // print matrix using PRIu32
            printf("%" PRIu32 " ", G->matrix[i][j]);
        }
        printf("\n");
    }
    

    // print if visited array 


}


