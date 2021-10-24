#include "dfs.h"

#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void dfs(Graph *G, uint32_t v, Path *curr, char *cities[], Path *shortest, int *counter,
    FILE *outfile, bool verbose) {
    *counter = *counter + 1;
    //printf("counter: %d\n", *counter);
    uint32_t num_vertices = graph_vertices(G);
    //printf("DFS current node, v = %d\n", v);
    uint32_t start_vertex = 0;

    graph_mark_visited(G, v);
    path_push_vertex(curr, v, G);
    for (uint32_t i = 0; i < num_vertices; i++) {
        //printf("current node: %d, other node: %d\n", v, i);
        if (graph_has_edge(G, v, i)) {
            if (graph_visited(G, i) == false) {
                if ((path_vertices(shortest) == 0) || (path_length(curr) < path_length(shortest))) {
                    dfs(G, i, curr, cities, shortest, counter, outfile, verbose);
                }
            }
        }
    }
    if (path_vertices(curr) == num_vertices) {
        if (graph_has_edge(G, v, START_VERTEX)) {
            //printf("####################### full path reached, path_vertices=%d, num_vertices=%d\n", path_vertices(curr), num_vertices);
            path_push_vertex(curr, START_VERTEX, G);
            if (verbose) {
                fprintf(outfile, "Path length: %d\n", path_length(curr));
                fprintf(outfile, "Path: ");
                path_print(curr, outfile, cities);
            }
            if (path_vertices(shortest) == 0) {
                path_copy(shortest, curr);
            } else {
                if (path_length(curr) < path_length(shortest)) {
                    path_copy(shortest, curr);
                }
            }
            path_pop_vertex(curr, &start_vertex, G);
        }
    }

    uint32_t i = 0;
    path_pop_vertex(curr, &i, G);
    graph_mark_unvisited(G, v);
}
