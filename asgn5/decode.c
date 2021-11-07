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

static FILE *input = NULL;
static FILE *input2 = NULL;
uint64_t hist[ALPHABET] = {0};
Code table[ALPHABET] = {0};
uint16_t permissions;
uint16_t unique_symbols;
uint64_t file_size;
int input_fd;
int output_fd = 1;


// void build_histogram() {
//     uint8_t buf = 0;
//     hist[0] = 1;
//     hist[255] = 1;
//     unique_symbols = 2;
//     while (true) {
//         buf = fgetc(input);
//         if (feof(input)) {
//             break;
//         }
//         if (hist[buf] == 0) {
//             unique_symbols++;
//         }
//         hist[buf]++;
//     }
// }

// void print_hist() {
//     for (uint64_t i = 0; i < ALPHABET; i++) {
//         if (hist[i] > 0) {
//             // printf("ASCII: %llu, %c, count: %llu\n", i, (char)i, hist[i]);
//         }
//     } 
// }

// Header header_create() {
//     Header h;
//     h.magic = MAGIC;
//     h.permissions = permissions;
//     h.tree_size = (3 * unique_symbols) - 1;
//     h.file_size = file_size;
//     return h;
// }

int main(int argc, char **argv) {
    int opt = 0;
    optind = 1;

    input = stdin;
    input2 = stdin;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
            case 'h':
                printf("SYNOPSIS\n\tA Huffman encoder.\n\tCompresses a file using the Huffman coding algorithm.\n\nUSAGE\n\t./encode [-h] [-i infile] [-o outfile]\n\nOPTIONS\n\t-h             Program usage and help.\n\t-v             Print compression statistics.\n\t-i infile      Input file to compress.\n\t-o outfile     Output of compressed data.\n");
                break;
            case 'i':
                // inputfile_name = optarg;
                input = fopen(optarg, "r");
                input2 = fopen(optarg, "r");
                input_fd = open(optarg, O_RDONLY);
                if(input == NULL) {
                    perror("Error opening infile");
                    return(-1);
                }
                struct stat stat_buf;
                if (stat(optarg, &stat_buf) == -1) {
                    perror("Error stating infile");
                    return(-1);
                }
                permissions = stat_buf.st_mode;
                file_size = stat_buf.st_size;
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

    uint8_t *tree_buf = (uint8_t *) malloc(h.tree_size);                
    read_bytes(input_fd, tree_buf, h.tree_size);
    Node *root = rebuild_tree(h.tree_size, tree_buf);
    
    // printf("first##########\n");
    //dump_tree(output_fd, root);
    // printf("##########\n");
    
    uint8_t bit = 0;
    Node *current_node = root;
    uint64_t i = 0;
    while (i < h.file_size) {
        read_bit(input_fd, &bit);
        // printf("bit read: %d\n", bit);
        if (bit == 0) {
            current_node = current_node->left;
            // node_print(current_node);
            if (current_node->left == NULL && current_node->right == NULL) {
                // printf("current node symbol: %d\n", current_node->symbol);
                write_bytes(output_fd, &(current_node->symbol), sizeof(current_node->symbol));
                i++;
                current_node = root;
            }
        } else {
            current_node = current_node->right;
            if (current_node->left == NULL && current_node->right == NULL) {
                // printf("current node symbol: %d\n", current_node->symbol);
                write_bytes(output_fd, &(current_node->symbol), sizeof(current_node->symbol));
                i++;
                current_node = root;
            }
        }
    }

    close(input_fd);
    close(output_fd);
    

}



