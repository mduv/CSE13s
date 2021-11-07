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
#include <sys/stat.h>
#include <sys/types.h>

#define OPTIONS "vhi:o:"

uint64_t hist[ALPHABET] = {0};
Code table[ALPHABET] = {0};
int input_fd;
int output_fd = 1;


int main(int argc, char **argv) {
    int opt = 0;
    optind = 1;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
            case 'h':
                printf("SYNOPSIS\n\tA Huffman encoder.\n\tCompresses a file using the Huffman coding algorithm.\n\nUSAGE\n\t./encode [-h] [-i infile] [-o outfile]\n\nOPTIONS\n\t-h             Program usage and help.\n\t-v             Print compression statistics.\n\t-i infile      Input file to compress.\n\t-o outfile     Output of compressed data.\n");
                break;
            case 'i':
                // inputfile_name = optarg;
                input_fd = open(optarg, O_RDONLY);
                if(input_fd < 0) {
                    perror("Error opening infile");
                    return(-1);
                }
                break;
            case 'o':
                output_fd = open(optarg, O_WRONLY | O_APPEND | O_CREAT);
                if (output_fd < 0) {
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
        }
    }

    /* Read in the header from infile and verify the magic number. If the magic number does not match
    0xBEEFD00D (defined as MAGIC in defines.h), then an invalid file was passed to your program.
    Display a helpful error message and quit. */
    Header h;
    Header *ptr_to_h = &h;
    uint8_t *ptr_to_bytes = (uint8_t *) ptr_to_h;
    read_bytes(input_fd, ptr_to_bytes, sizeof(Header));
    if (h.magic != MAGIC) {
        perror("Error: magic number does not match");
        return -1;
    }

    printf("h.magic:%X, h.permissions:%X, h.tree_size:%X, h.file_size:%llX\n", h.magic, h.permissions, h.tree_size, h.file_size);
    fchmod(output_fd, h.permissions);

    // Rebuild tree from the bytes read from the file
    uint8_t *tree_buf = (uint8_t *) malloc(h.tree_size);                
    read_bytes(input_fd, tree_buf, h.tree_size);
    Node *root = rebuild_tree(h.tree_size, tree_buf);
    
    uint8_t bit = 0;
    Node *current_node = root;
    uint64_t i = 0;
    while (i < h.file_size) {
        read_bit(input_fd, &bit);
        if (bit == 0) {
            current_node = current_node->left;
            if (current_node->left == NULL && current_node->right == NULL) {
                write_bytes(output_fd, &(current_node->symbol), sizeof(current_node->symbol));
                i++;
                current_node = root;
            }
        } else {
            current_node = current_node->right;
            if (current_node->left == NULL && current_node->right == NULL) {
                write_bytes(output_fd, &(current_node->symbol), sizeof(current_node->symbol));
                i++;
                current_node = root;
            }
        }
    }

    close(input_fd);
    close(output_fd);
}



