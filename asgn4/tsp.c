#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"
#include <string.h>
#include "dfs.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdbool.h>



#define OPTIONS "uvhi:o:"

static FILE *input = NULL;
static FILE *output = NULL;

int main(int argc, char **argv) {
    int opt = 0;
    optind = 1;
    bool undirected = false;
    bool verbose = false;
    uint32_t vertices = 0;
    char **cities;


    input = stdin;
    output = stdout;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
            case 'h':
                printf("SYNOPSIS\n\tTraveling Salesman Problem using DFS."
                   "\n\nUSAGE\n"
                   "\t../tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n\nOPTIONS\n "
                   "\t-u             Use undirected graph."
                   "\n \t-v             Enable verbose printing.\n \t-h             Program usage and help.\n \t"
                   "\n \t-i infile      Input containing graph (default: stdin)"
                   "\n \t-o outfile     Output of computed path (default: stdout)\n");
                   return(-1);
                break;
            case 'i':
                // inputfile_name = optarg;
                input = fopen(optarg, "r");
                if(input == NULL) {
                    perror("Error opening infile");
                    return(-1);
                }
                break;
            case 'o':
                output = fopen(optarg, "w");
                if(output == NULL) {
                    perror("Error opening outfile");
                    return(-1);
                }
                break;
            case 'u':
                undirected = 1;
                break;
            case 'v':
                verbose = 1;
                break;
            return 0;
        // default:
        //     printf();
        }
    }
    char buf[1024];

    if( fgets (buf, 60, input)  != NULL ) {
      /* writing content to stdout */
      vertices = atoi(buf);
    }
    if (vertices <= 0 || vertices >= VERTICES) {
        fprintf(output, "Error: malformed number of vertices");
        return (-1);
    }
    cities = (char **)malloc(vertices * sizeof(char *));
    for (uint32_t i = 0; i < vertices; i++) {
        if( fgets (buf, 1204, input)  != NULL ) {
            buf[strlen(buf)-1] = '\0'; // get rid of new line
            cities[i] = strdup(buf);

        } 
    }

    Graph *locations = graph_create(vertices, undirected);
    uint32_t i = 0;
    uint32_t j = 0;
    uint32_t k = 0;
    if (locations == NULL) {
        fprintf(stderr, "error");       //print stderror to stderr using printf
        graph_delete(&locations);
        return 1;
    }

    while(!feof(input)) {
            int num_params = fscanf(input, "%u %u %u", &i, &j, &k);
            if (num_params == 0) {
                fprintf(output, "Error: malformed edge.\n");
                return(-1);
            }
            graph_add_edge(locations, i, j, k);
    }

    Path *curr = path_create();
    Path *shortest = path_create();

    int counter = 0;

    //graph_print(locations);

    dfs(locations, START_VERTEX, curr, cities, shortest, &counter, output, verbose);

    // Print shortest path
    fprintf(output, "Path length: %d\n", path_length(shortest));
    fprintf(output, "Path: ");
    path_print(shortest, output, cities);

    // Print total number of recursive calls
    fprintf(output, "Total recursive calls: %d\n", counter);
}
