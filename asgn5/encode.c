#include "code.h"
#include "defines.h"
#include "node.h"
#include "huffman.h"
#include <string.h>
#include "stack.h"
#include "pq.h"
#include "header.h"
#include "io.h"


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <stdbool.h>
#include <fcntl.h>

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


    // Node *test_node_left = node_create('a', 20);
    // Node *test_node_right = node_create('b', 1);
    // Node *test_node_middle = node_create('c', 10);
    // Node *test_node_parent = node_join(test_node_left, test_node_right);
    // node_print(test_node_parent);
    // Node *test_extra = node_create('z', 10);

    // PriorityQueue *test_pq = pq_create(3);
    
    // enqueue(test_pq, test_node_left);
    // enqueue(test_pq, test_node_right);
    // enqueue(test_pq, test_node_middle);
    // dequeue(test_pq, &test_node_middle);
    //dequeue(test_pq, &test_node_left);
    //printf("%d\n", dequeue(test_pq, &test_extra));
    // pq_print(test_pq);
    // pq_print(test_pq);
    // dequeue(test_pq, &test_node_right);
    // dequeue(test_pq, &test_node_left);
    // pq_print(test_pq);

    // pq_print(test_pq);
    //node_print(test_node_right);

//  return enqueue(test_pq, test_node_left);
//  return 1;
    // uint8_t x = 0;
    // Code c = code_init();
    // code_push_bit(&c, 1);
    // code_push_bit(&c, 0);
    // code_push_bit(&c, 1);
    // code_print(&c);
    // printf("\n");
    
    // printf("\ncode_pop returned: %d popped bit:%d\n", code_pop_bit(&c, &x),  x);
    // code_print(&c);
    // printf("\ncode_pop returned: %d popped bit:%d\n", code_pop_bit(&c, &x),  x);
    // code_print(&c);
    // printf("\ncode_pop returned: %d popped bit:%d\n", code_pop_bit(&c, &x),  x);
    // code_print(&c);
    // printf("\ncode_pop returned: %d popped bit:%d\n", code_pop_bit(&c, &x),  x);
    // code_print(&c);
    // printf("\ncode_pop returned: %d popped bit:%d\n", code_pop_bit(&c, &x),  x);
    // code_print(&c)

    // int x = read_bytes(test.txt, uint8_t *buf, int nbytes) 
    // printf( )
    uint8_t buf[1000000];   // 1mil
    // int filedesc = open("test.txt", O_RDONLY);
    // printf("num of bytes read: %d\n", read_bytes(filedesc, buf, 1000000));
    int filedesc = open("testwrite.txt", O_WRONLY);
    printf("num of bytes written: %d\n", write_bytes(filedesc, buf, 1000000));
   // printf("%s", buf);

}


