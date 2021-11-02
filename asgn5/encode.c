#include "code.h"
#include "defines.h"
#include "node.h"
#include "huffman.h"
#include <string.h>
#include "stack.h"
#include "pq.h"
#include "header.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdbool.h>

#define OPTIONS "vhi:o:"

static FILE *input = NULL;
static FILE *output = NULL;

int main(int argc, char **argv) {
    int opt = 0;
    optind = 1;


    input = stdin;
    output = stdout;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
            case 'h':
                printf("SYNOPSIS\n\tA Huffman encoder.\n\tCompresses a file using the Huffman coding algorithm.\n\nUSAGE\n\t./encode [-h] [-i infile] [-o outfile]\n\nOPTIONS\n\t-h             Program usage and help.\n\t-v             Print compression statistics.\n\t-i infile      Input file to compress.\n\t-o outfile     Output of compressed data.\n");
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
            // case 'u':
            //     undirected = 1;
            //     break;
            // case 'v':
            //     verbose = 1;
            //     break;
            return 0;
        // default:
        //     printf();
        }
    }


    Node *test_node_left = node_create('a', 2);
    Node *test_node_right = node_create('b', 3);
    Node *test_node_parent = node_join(test_node_left, test_node_right);
    node_print(test_node_parent);
    return 1;

}


