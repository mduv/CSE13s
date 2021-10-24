#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"
// #include "dfs.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdbool.h>



// #define OPTIONS "uvhi:o:"

// static FILE *input = NULL;
// static FILE *output = NULL;

// // any other static variables

// // helper for proccesing files
// // process_files(char *infile_name, char *outfile_name) {
// //     input = fopen(infile_name, "r") {

// //     }
// //     input = fopen(outfile_name, "r") {
        
// //     }

// //     return true;
// // }

// int main(int argc, char **argv) {
//     int opt = 0;
//     optind = 1;
//     char *inputfile_name = NULL;
//     // char *outputfile_name = NULL;
//     bool undirected = false;
//     uint32_t vertices;

//     while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
//         switch (opt) {
//             case 'h':
//                 printf("SYNOPSIS\nSYNOPSIS\n\tTraveling Salesman Problem using DFS."
//                    "\n\nUSAGE\n"
//                    "\t../tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n\nOPTIONS\n "
//                    "\t-u             Use undirected graph."
//                    "\n \t-v             Enable verbose printing.\n \t-h             Program usage and help.\n \t"
//                    "\n \t-i infile      Input containing graph (default: stdin)"
//                    "\n \t-o outfile     Output of computed path (default: stdout)");
//                 break;
//             case 'i':
//                 inputfile_name = optarg;
//                 break;
//             return 0;
//         // default:
//         //     printf();
//         }
//     }


//     return 0;

//     input = stdin;
//     output = stdout;

//     Graph *locations = graph_create(vertices, undirected);

//     if (locations == NULL) {
//         // printf(stderr, "%s", "error");       //print stderror to stderr using printf
//         graph_delete(&locations);
//         return 1;
//     }

//     path_create();  // call path create
//     // call dfs function
//     // print shortest path
//     // clean up memory
//     // return 0;

// }




int main() {
    struct Graph *graph = graph_create(10, true);

    char *cities[4];
    
    cities[0] = "A"; 
    cities[1] = "B"; 
    cities[2] = "C"; 
    cities[3] = "D"; 
    graph_add_edge(graph, 0, 1, 100);
    graph_add_edge(graph, 1, 2, 250);
    graph_add_edge(graph, 2, 3, 375);
    graph_add_edge(graph, 3, 0, 425);
    // graph_add_edge(graph, 2, 0, 2);
    // graph_add_edge(graph, 2, 1, 1);
    graph_print(graph);
    // printf("%d", graph_add_edge(graph, 0, 2, 2));
    // printf("\n%d", graph_edge_weight(graph, -1, 1));


    struct Path *path1 = path_create();
    path_push_vertex(path1, 0, graph);
    path_push_vertex(path1, 1, graph);
    path_push_vertex(path1, 2, graph);
    
    // path_push_vertex(path1, 3, graph);

    printf("path1 -> %d\n", path_length(path1));
    path_print(path1, stdout, cities);

    // printf("%d\n", path_push_vertex(path1, 2, graph));
    // printf("\n%d", path_length(path1));

    struct Path *path2 = path_create();
    path_push_vertex(path2, 2, graph);
    // path_push_vertex(path2, 3, graph);
    printf("path2 -> %d\n", path_length(path2));
    path_print(path2, stdout, cities);


    
    path_copy(path2, path1);
    printf("path1 -> %d\n", path_length(path1));
    path_print(path1, stdout, cities);
    printf("path2 -> %d\n", path_length(path2));
    path_print(path2, stdout, cities);


    // printf("\n%d", path_vertices(path1));
    // printf("\n%d", path_vertices(path2));
    // printf("\n%d", path_length(path2));


    // path_print(path, stdout, *cities[]);


    


    
    // path_print(path, *output, *cities[]);

}
